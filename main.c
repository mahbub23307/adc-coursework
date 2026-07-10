#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int main()
{
    FileHeader header;

    if (!readHeader("adc_sensor_log.bin", &header))
    {
        return 1;
    }

    printf("Header Information\n");
    printf("------------------\n");
    printf("Magic Number : %u\n", header.magic);
    printf("Version : %u\n", header.version);
    printf("Channels : %u\n", header.channel_count);
    printf("Records : %u\n", header.record_count);
    printf("Sample Rate : %u Hz\n", header.sample_rate_hz);

    /* Allocate memory for converted samples */
    ADCSample *samples;

    samples = malloc(header.record_count * sizeof(ADCSample));

    if (samples == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("\nMemory allocated successfully for %u samples.\n",
           header.record_count);

    /* Allocate memory for binary samples */
    ADCSampleBinary *binarySamples;

    binarySamples = malloc(header.record_count * sizeof(ADCSampleBinary));

    if (binarySamples == NULL)
    {
        printf("Memory allocation failed!\n");
        free(samples);
        return 1;
    }

    /* Read all binary samples */
    if (!readAllSamples("adc_sensor_log.bin",
                        binarySamples,
                        header.record_count))
    {
        printf("Failed to read all samples!\n");
        free(binarySamples);
        free(samples);
        return 1;
    }

    printf("Successfully read %u samples.\n",
           header.record_count);

    /* Read and display the first sample */
    ADCSampleBinary sample;

    if (readFirstSample("adc_sensor_log.bin", &sample))
    {
        printf("\nFirst Sample\n");
        printf("------------\n");
        printf("Timestamp : %.3f\n", sample.timestamp);
        printf("Channel : %u\n", sample.channel_id);
        printf("Raw Value : %u\n", sample.raw_value);
        printf("Temp : %d\n", sample.temperature);
        printf("Status : %u\n", sample.status_flags);
        printf("Sequence : %u\n", sample.sequence_number);
    }

    /* Free allocated memory */
    free(binarySamples);
    free(samples);

    return 0;
}