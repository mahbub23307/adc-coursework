//
// Created by m43-hasan on 08/07/2026.
#ifndef STATS_H
#define STATS_H

#include "adc.h"

void convertSamples(ADCSampleBinary *binarySamples,
                    ADCSample *samples,
                    uint32_t count);
typedef struct
{
    float mean;
    float minimum;
    float maximum;
    float standardDeviation;

    uint32_t overVoltageCount;
    uint32_t underVoltageCount;
    uint32_t sensorFaultCount;

} ChannelStats;
typedef struct
{
    uint32_t missingCount;
    uint32_t outOfOrderCount;
} IntegrityStats;
void calculateStatistics(ADCSample *samples,
                         uint32_t count,
                         ChannelStats stats[]);
void checkSamplingIntegrity(ADCSample *samples,
                            uint32_t count,
                            IntegrityStats *integrity);

#endif