//
// Created by m43-hasan
//
#ifndef ADC_H
#define ADC_H

#include <stdint.h>

/*
 * File header (24 bytes)
 */
#pragma pack(push,1)

typedef struct
{
    uint32_t magic;
    uint16_t version;
    uint16_t channel_count;
    uint32_t record_count;
    uint32_t sample_rate_hz;
    uint8_t reserved[8];

} FileHeader;


/*
 * Binary record (16 bytes)
 */
typedef struct
{
    float timestamp;
    uint8_t channel_id;
    uint16_t raw_value;
    int16_t temperature;
    uint8_t status_flags;
    uint32_t sequence_number;
    uint8_t reserved[2];

} ADCSampleBinary;

#pragma pack(pop)


/*
 * Coursework sample structure
 */
typedef struct
{
    float timestamp;

    uint8_t channel_id;

    uint16_t raw_value;

    float voltage;

    int16_t temperature;

    uint8_t status_flags;

    uint32_t sequence_number;

} ADCSample;

#endif