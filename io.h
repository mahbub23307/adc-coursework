//
// Created by m43-hasan on 08/07/2026.
#ifndef IO_H
#define IO_H

#include "adc.h"

int readHeader(const char *filename, FileHeader *header);
int readFirstSample(const char *filename, ADCSampleBinary *sample);

#endif