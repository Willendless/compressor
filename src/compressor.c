#include "util.h"
#include "compressor.h"
#include "buffer.h"
#include "symtable.h"
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const static int bitsmask[9] = {0, 1, 3, 7, 15, 31, 63, 127, 255};

int encode(compressor* c, int val, FILE *out)
{
	assert(c);
	assert(out);
	data_buffer *tmp = value(&c->symtable, val);	
	int ret = 0;


	tmp = insert(tmp, &c->buf);
	if (tmp != NULL) {	//缓冲区溢出则flush，并替换
			ret += flush(c, out);
			bufcpy(tmp, &(c->buf));
	}
	return ret;
}

int flush(compressor* c, FILE *out)
{
	data_buffer *p = &(c->buf);
	int i, ret = p->len;
	for (i = 0; i < p->len; i += 8) {
			fprintf(out, "%c", p->databuf[i/8]&bitsmask[8 > p->len-i?p->len-i:8]);
	}
	clear_buf(&c->buf);
	return ret;
}

void update_table(compressor* c, symbol_table* s)
{
	load(&c->symtable, s);
}


void compressor_free(compressor *c)
{
	release_tree(c->root);
}
