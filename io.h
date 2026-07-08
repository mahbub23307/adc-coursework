//
// Created by m43-hasan on 08/07/2026.
#ifndef IO_H
#define IO_H

#include "adc.h"

int readHeader(const char *filename, FileHeader *header);
int readFirstSample(const char *filename, ADCSampleBinary *sample);
int readAllSamples(const char *filename, ADCSampleBinary samples[], uint32_t count);
int readAllSamples(const char *filename,
                   ADCSampleBinary samples[],
                   uint32_t count);
#endif