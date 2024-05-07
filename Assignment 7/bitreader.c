#include "bitreader.h"

#include <stdio.h>
#include <stdlib.h>

struct BitReader {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitReader *bit_read_open(const char *filename) {
    BitReader *reader = malloc(sizeof(BitReader));
    if (reader == NULL) {
        return NULL;
    }

    FILE *f = fopen(filename, "rb");
    if (f == NULL) {
        free(reader);
        return NULL;
    }

    reader->byte = 0;
    reader->bit_position = 8;
    reader->underlying_stream = f;
    return reader;
}

void bit_read_close(BitReader **pbuf) {
    if (*pbuf != NULL) {
        if (fclose((*pbuf)->underlying_stream) != 0) {
            exit(EXIT_FAILURE);
        }

        free(*pbuf);
        *pbuf = NULL;
    }
}

uint8_t bit_read_bit(BitReader *buf) {
    if (buf->bit_position > 7) {
        buf->byte = (uint8_t) fgetc(buf->underlying_stream);
        if (ferror(buf->underlying_stream)) {
            exit(EXIT_FAILURE);
        }

        buf->bit_position = 0;
    }

    uint8_t bit = (buf->byte >> buf->bit_position) & 1;
    buf->bit_position++;
    return bit;
}

uint8_t bit_read_uint8(BitReader *buf) {
    uint8_t byte = 0x00;
    for (int i = 0; i < 8; i++) {
        uint8_t bit = bit_read_bit(buf);
        byte |= (bit << i);
    }
    return byte;
}

uint16_t bit_read_uint16(BitReader *buf) {
    uint16_t byte = 0x0000;
    for (int i = 0; i < 16; i++) {
        uint8_t bit = bit_read_bit(buf);
        byte |= (bit << i);
    }
    return byte;
}

uint32_t bit_read_uint32(BitReader *buf) {
    uint32_t byte = 0x00000000;
    for (int i = 0; i < 32; i++) {
        uint8_t bit = bit_read_bit(buf);
        byte |= ((unsigned int) bit << i);
    }
    return byte;
}
