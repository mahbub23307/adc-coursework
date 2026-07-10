//
// Created by m43-hasan on 08/07/2026.
#ifndef STATS_H
#define STATS_H

#include "adc.h"

void convertSamples(ADCSampleBinary *binarySamples,
                    ADCSample *samples,
                    uint32_t count);

#endif