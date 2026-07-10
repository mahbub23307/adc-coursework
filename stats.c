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

        /* Voltage will be calculated in Requirement 5 */
        dst->voltage = (src->raw_value / 4095.0f) * 3.3f;

        src++;
        dst++;
    }
}