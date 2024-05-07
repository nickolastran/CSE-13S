#include "bitreader.h"
#include "bitwriter.h"
#include "node.h"
#include "pq.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "i:o:h"

typedef struct Code {
    uint8_t code_length;
    int64_t code;
} Code;

uint32_t fill_histogram(FILE *fin, uint32_t *histogram) {
    for (int i = 0; i < 256; i++) {
        histogram[i] = 0;
    }

    uint32_t filesize = 0;
    int byte;

    while ((byte = fgetc(fin)) != EOF) {
        ++histogram[byte];
        ++filesize;
    }
    ++histogram[0x00];
    ++histogram[0xff];
    return filesize;
}

Node *create_tree(uint32_t *histogram, uint16_t *num_leaves) {
    PriorityQueue *pq = pq_create();
    uint16_t leaf = 0;

    for (int i = 0; i < 256; i++) {
        if (histogram[i] != 0) {
            Node *node = node_create((uint8_t) i, histogram[i]);
            enqueue(pq, node);
            leaf++;
        }
    }
    *num_leaves = leaf;
    while (!pq_size_is_1(pq)) {
        Node *left = dequeue(pq);
        Node *right = dequeue(pq);
        Node *combined = node_create(0, (left->weight + right->weight));
        combined->left = left;
        combined->right = right;
        enqueue(pq, combined);
    }

    Node *root = dequeue(pq);
    pq_free(&pq);
    return root;
}

void fill_code_table(Code *code_table, Node *node, uint64_t code, uint8_t code_length) {
    if (node->left != NULL) {
        fill_code_table(code_table, node->left, code, code_length + 1);
        code |= 1 << code_length;
        fill_code_table(code_table, node->right, code, code_length + 1);
    } else {
        code_table[node->symbol].code = code;
        code_table[node->symbol].code_length = code_length;
    }
}

void huff_write_tree(BitWriter *outbuf, Node *node) {
    if (node->left == NULL) {
        bit_write_bit(outbuf, 1);
        bit_write_uint8(outbuf, node->symbol);
    } else {
        huff_write_tree(outbuf, node->left);
        huff_write_tree(outbuf, node->right);
        bit_write_bit(outbuf, 0);
    }
}

void huff_compress_file(BitWriter *outbuf, FILE *fin, uint32_t filesize, uint16_t num_leaves,
    Node *code_tree, Code *code_table) {
    bit_write_uint8(outbuf, 'H');
    bit_write_uint8(outbuf, 'C');
    bit_write_uint32(outbuf, filesize);
    bit_write_uint16(outbuf, num_leaves);
    huff_write_tree(outbuf, code_tree);
    while (true) {
        int b = fgetc(fin);
        if (b == EOF) {
            break;
        }
        uint64_t code = code_table[b].code;
        uint8_t code_length = code_table[b].code_length;
        for (int i = 0; i < code_length; i++) {
            bit_write_bit(outbuf, code & 1);
            code >>= 1;
        }
    }
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
        fprintf(stderr, "Huff: -i option is required\n");
        fprintf(stderr, "Usage: Huff -i infile -o outfile\n");
        fprintf(stderr, "       Huff -v -i infile -o outfile\n");
        fprintf(stderr, "       Huff -h\n");
        return 0;
    }

    if (!I & !O) {
        fprintf(stderr, "Huff: -i option is required\n");
        fprintf(stderr, "Usage: Huff -i infile -o outfile\n");
        fprintf(stderr, "       Huff -v -i infile -o outfile\n");
        fprintf(stderr, "       Huff -h\n");
        return 0;
    } else if (!I) {
        fprintf(stdout, "-i file is required\n");
        fprintf(stderr, "Usage: Huff -i infile -o outfile\n");
        fprintf(stderr, "       Huff -v -i infile -o outfile\n");
        fprintf(stderr, "       Huff -h\n");
        return 0;
    } else if (!O) {
        fprintf(stdout, "-o file is required\n");
        fprintf(stderr, "Usage: Huff -i infile -o outfile\n");
        fprintf(stderr, "       Huff -v -i infile -o outfile\n");
        fprintf(stderr, "       Huff -h\n");
        return 0;
    }

    uint16_t num_leaves = 0;
    uint32_t histogram[256];
    FILE *fin;
    fin = fopen(inN, "rb");
    uint32_t filesize = fill_histogram(fin, histogram);
    Node *code_tree = create_tree(histogram, &num_leaves);
    Code code_table[256];

    fill_code_table(code_table, code_tree, 0, 0);
    BitWriter *outbuf = bit_write_open(outN);
    fseek(fin, 0, SEEK_SET);
    huff_compress_file(outbuf, fin, filesize, num_leaves, code_tree, code_table);
    node_free(&code_tree);
    bit_write_close(&outbuf);
    if (fin != NULL) {
        fclose(fin);
    }
    return 0;
}
