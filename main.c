
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

    return 0;
}