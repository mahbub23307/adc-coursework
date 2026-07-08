#include <stdio.h>
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

    return 0;
}