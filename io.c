//
// Created by m43-hasan on 08/07/2026.
//

#include <stdio.h>
#include "io.h"

int readHeader(const char *filename, FileHeader *header)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        return 0;
    }

    if (fread(header, sizeof(FileHeader), 1, file) != 1)
    {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}

int readFirstSample(const char *filename, ADCSampleBinary *sample)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        return 0;
    }

    FileHeader header;

    if (fread(&header, sizeof(FileHeader), 1, file) != 1)
    {
        fclose(file);
        return 0;
    }

    if (fread(sample, sizeof(ADCSampleBinary), 1, file) != 1)
    {
        fclose(file);
        return 0;
    }

    fclose(file);
    return 1;
}