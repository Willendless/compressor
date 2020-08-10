#include "symtable.h"
#include "buffer.h"
#include <stdio.h>
#include <assert.h>
#include "util.h"

void init_symtable(symbol_table *symtable, data_buffer *symbols)
{
	assert(symbols != NULL);
	assert(symtable != NULL);
	int i;
	for (i = 0; i < SYMBOL_NUM; i++) {
			bufcpy(&symbols[i], &symtable->symbols[i]);
	//		printf("symtable.c: init_symtable: symbols_len: %d\n", symbols[i].len);
	}
}

data_buffer *value(symbol_table *symtable, int var)
{
	//printf("symtable.c: value: var: %d\n", var);
	//printf("symtable.c: value:var: %c len: %d\n", var, symtable->symbols[var].len);
	assert(var<=255&&var>=0);
	return &(symtable->symbols[var]);
}

void load(symbol_table *from, symbol_table *to)
{
	int i;
	for (i = 0; i < SYMBOL_NUM; i++)
			bufcpy(&to->symbols[i], &from->symbols[i]);
}
