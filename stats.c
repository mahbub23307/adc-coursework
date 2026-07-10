#include <math.h>
#include "stats.h"

void convertSamples(ADCSampleBinary *binarySamples,
                    ADCSample *samples,
                    uint32_t count)
{
    ADCSampleBinary *src = binarySamples;
    ADCSample *dst = samples;

    for (uint32_t i = 0; i < count; i++)
    {
        dst->timestamp = src->timestamp;
        dst->channel_id = src->channel_id;
        dst->raw_value = src->raw_value;
        dst->temperature = src->temperature;
        dst->status_flags = src->status_flags;
        dst->sequence_number = src->sequence_number;

        /* Voltage calculated in Requirement 5 */
        dst->voltage = (src->raw_value / 4095.0f) * 3.3f;

        src++;
        dst++;
    }
}

void calculateStatistics(ADCSample *samples,
                         uint32_t count,
                         ChannelStats stats[])
{
    ADCSample *sample = samples;

    float sum[4] = {0};
    uint32_t sampleCount[4] = {0};
    float varianceSum[4] = {0};

    /* Initialise minimum and maximum */
    for (uint32_t i = 0; i < 4; i++)
    {
        stats[i].minimum = 3.3f;
        stats[i].maximum = 0.0f;

        stats[i].overVoltageCount = 0;
        stats[i].underVoltageCount = 0;
        stats[i].sensorFaultCount = 0;
    }

    /* First pass: sum, min, max */
    for (uint32_t i = 0; i < count; i++)
    {
        sum[sample->channel_id] += sample->voltage;
        sampleCount[sample->channel_id]++;

        if (sample->voltage < stats[sample->channel_id].minimum)
        {
            stats[sample->channel_id].minimum = sample->voltage;
        }

        if (sample->voltage > stats[sample->channel_id].maximum)
        {
            stats[sample->channel_id].maximum = sample->voltage;
        }
        if (sample->voltage > 3.0f)
        {
            stats[sample->channel_id].overVoltageCount++;
        }
        if (sample->voltage < 0.3f)
        {
            stats[sample->channel_id].underVoltageCount++;
        }
        if (sample->status_flags & 0x01)
        {
            stats[sample->channel_id].sensorFaultCount++;
        }
        sample++;
    }

    /* Calculate mean */
    for (uint32_t i = 0; i < 4; i++)
    {
        if (sampleCount[i] > 0)
        {
            stats[i].mean = sum[i] / sampleCount[i];
        }
        else
        {
            stats[i].mean = 0.0f;
        }
    }

    /* Second pass: variance */
    sample = samples;

    for (uint32_t i = 0; i < count; i++)
    {
        float difference = sample->voltage - stats[sample->channel_id].mean;

        varianceSum[sample->channel_id] += difference * difference;

        sample++;
    }

    /* Calculate standard deviation */
    for (uint32_t i = 0; i < 4; i++)
    {
        if (sampleCount[i] > 0)
        {
            stats[i].standardDeviation =
                    sqrt(varianceSum[i] / sampleCount[i]);
        }
        else
        {
            stats[i].standardDeviation = 0.0f;
        }
    }
}
void checkSamplingIntegrity(ADCSample *samples,
                            uint32_t count,
                            IntegrityStats *integrity)
{
    integrity->missingCount = 0;
    integrity->outOfOrderCount = 0;

    if (count == 0)
    {
        return;
    }

    for (uint32_t i = 1; i < count; i++)
    {
        uint32_t previous = samples[i - 1].sequence_number;
        uint32_t current = samples[i].sequence_number;

        if (current == previous + 1)
        {
            /* Correct sequence */
        }
        else if (current > previous + 1)
        {
            integrity->missingCount += current - previous - 1;
        }
        else
        {
            integrity->outOfOrderCount++;
        }
    }
}