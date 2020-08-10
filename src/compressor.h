#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "symtable.h"
#include <stdio.h>
#include "huffman.h"

typedef struct {
		data_buffer buf;
		symbol_table symtable;
		HuffmanTree root;
}compressor;

int encode(compressor*, int var, FILE *out);
int flush(compressor*, FILE *out);
void update_table(compressor*, symbol_table*);
void compressor_free(compressor*);

#endif
