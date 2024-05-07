#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

void dehuff_decompress_file(FILE *fout, BitReader *inbuf) {
    uint8_t type1 = bit_read_uint8(inbuf);
    uint8_t type2 = bit_read_uint8(inbuf);
    uint32_t filesize = bit_read_uint32(inbuf);
    uint16_t num_leaves = bit_read_uint16(inbuf);
    assert(type1 == 'H');
    assert(type2 == 'C');
    uint16_t num_nodes = 2 * num_leaves - 1;
    Node *stack[64];
    int top_pointer = -1;
    Node *node;

    for (int i = 0; i < num_nodes; i++) {
        uint8_t bit = bit_read_bit(inbuf);
        if (bit == 1) {
            uint8_t symbol = bit_read_uint8(inbuf);
            node = node_create(symbol, 0);
        } else {
            node = node_create(0, 0);
            node->right = stack[top_pointer--];
            node->left = stack[top_pointer--];
        }
        stack[++top_pointer] = node;
    }

    Node *code_tree = stack[top_pointer--];
    for (uint32_t m = 0; m < filesize; m++) {
        node = code_tree;
        while (true) {
            uint8_t bit = bit_read_bit(inbuf);
            if (bit == 0) {
                node = node->left;
            } else {
                node = node->right;
            }

            if (node->left == NULL && node->right == NULL) {
                break;
            }
        }
        fputc(node->symbol, fout);
    }
    node_free(&code_tree);
}

int main(int argc, char **argv) {
    int opt;
    char *inN;
    char *outN;
    bool I = 0;
    bool O = 0;
    bool H = 0;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            I = true;
            inN = optarg;
            break;
        case 'o':
            O = true;
            outN = optarg;
            break;
        case 'h': H = true;
        default: H = true; break;
        }
    }

    if (H) {
        fprintf(stderr, "Dehuff: -i option is required\n");
        fprintf(stderr, "Usage: Dehuff -i infile -o outfile\n");
        fprintf(stderr, "       Dehuff -v -i infile -o outfile\n");
        fprintf(stderr, "       Dehuff -h\n");
        return 0;
    }

    if (!I & !O) {
        fprintf(stderr, "Dehuff: -i option is required\n");
        fprintf(stderr, "Usage: Dehuff -i infile -o outfile\n");
        fprintf(stderr, "       Dehuff -v -i infile -o outfile\n");
        fprintf(stderr, "       Dehuff -h\n");
        return 0;
    } else if (!I) {
        fprintf(stdout, "-i file is required\n");
        fprintf(stderr, "Usage: Dehuff -i infile -o outfile\n");
        fprintf(stderr, "       Dehuff -v -i infile -o outfile\n");
        fprintf(stderr, "       Dehuff -h\n");
        return 0;
    } else if (!O) {
        fprintf(stdout, "-o file is required\n");
        fprintf(stderr, "Usage: Dehuff -i infile -o outfile \n");
        fprintf(stderr, "       Dehuff -v -i infile -o outfile\n");
        fprintf(stderr, "       Dehuff -h\n");
        return 0;
    }

    BitReader *inbuf = bit_read_open(inN);
    FILE *fout = fopen(outN, "wb");
    dehuff_decompress_file(fout, inbuf);
    bit_read_close(&inbuf);
    fclose(fout);
    return 0;
}
