//
// Created by m43-hasan on 08/07/2026.
#include <stdio.h>
#include <stdint.h>
#include "io.h"

int readHeader(const char *filename, FileHeader *header)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    if (fread(header, sizeof(FileHeader), 1, file) != 1)
    {
        printf("Error reading header.\n");
        fclose(file);
        return 0;
    }
    if (header->magic != 2915155695U)
    {
        printf("Invalid file format.\n");
        fclose(file);
        return 0;
    }

    fclose(file);

    return 1;
}

