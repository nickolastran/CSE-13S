#include "bitwriter.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

struct BitWriter {
    FILE *underlying_stream;
    uint8_t byte;
    uint8_t bit_position;
};

BitWriter *bit_write_open(const char *filename) {
    BitWriter *writer = (BitWriter *) malloc(sizeof(BitWriter));
    writer->underlying_stream = fopen(filename, "wb");
    if (writer->underlying_stream == NULL) {
        free(writer);
        return NULL;
    }
    writer->byte = 0x00;
    writer->bit_position = 0;
    return writer;
}

void bit_write_close(BitWriter **pbuf) {
    if (*pbuf != NULL) {
        if ((*pbuf)->bit_position > 0) {
            if (fputc((*pbuf)->byte, (*pbuf)->underlying_stream) == EOF) {
                exit(EXIT_FAILURE);
            }
        }
        if (fclose((*pbuf)->underlying_stream) != 0) {
            exit(EXIT_FAILURE);
        }
        free(*pbuf);
        *pbuf = NULL;
    }
}

void bit_write_bit(BitWriter *buf, uint8_t bit) {
    if (buf == NULL) {
        return;
    }

    if (buf->bit_position > 7) {
        if (fputc(buf->byte, buf->underlying_stream) == EOF) {
            exit(EXIT_FAILURE);
        }
        buf->byte = 0x00;
        buf->bit_position = 0;
    }
    buf->byte |= (bit << buf->bit_position);
    buf->bit_position++;
}

void bit_write_uint8(BitWriter *buf, uint8_t byte) {
    for (int i = 0; i < 8; i++) {
        bit_write_bit(buf, (byte >> i) & 1);
    }
}

void bit_write_uint16(BitWriter *buf, uint16_t x) {
    for (int i = 0; i < 16; i++) {
        bit_write_bit(buf, (x >> i) & 1);
    }
}

void bit_write_uint32(BitWriter *buf, uint32_t x) {
    for (int i = 0; i < 32; i++) {
        bit_write_bit(buf, (x >> i) & 1);
    }
}
