#ifndef _SYMTABLE_H
#define _SYMTABLE_H

#include "buffer.h"

#define SYMBOL_NUM 256

typedef struct {
		data_buffer symbols[SYMBOL_NUM];
} symbol_table;

void init_symtable(symbol_table *symtable, data_buffer *symbols);
void load(symbol_table *from, symbol_table *to);
data_buffer *value(symbol_table *symtable, int val);

#endif
