#include "decoder.h"
#include "huffman.h"
#include <assert.h>
#include <stdlib.h>
#define T Decoder_T

struct Decoder {
	HuffmanTree root;
	int redund;
};

T Decoder_new(FILE *f)
{
	int ch;
	int redund;
	T ret = malloc(sizeof(struct Decoder));
	ret->root = malloc(sizeof(Node));
	assert(f);
	
	fscanf(f, "%d", &redund);
	ret->redund = redund == 0? 8: redund;
	while ((ch = getc(f)) == ' ') {
		HuffmanTree p = ret->root;
		int tmp;
		while ((ch = getc(f)) != ' ') {
			assert(ch == '1' || ch == '0');
			if (ch == '1') {
				if (!p->r_child) {
					p->r_child = malloc(sizeof(Node));
				}
				p = p->r_child;
			}
			else {
				if (!p->l_child) {
					p->l_child = malloc(sizeof(Node));
				}
				p = p->l_child;
			}
		}
		fscanf(f, "%d", &tmp);
		p->ch = tmp;
		//printf("new_decoder: 46: %c\n", tmp);
	}
	return ret;
}

void Decoder_decode(T decoder, FILE *in, FILE *out)
{
	assert(in && out && decoder && decoder->root);
	HuffmanTree p = decoder->root;
	int cur = fgetc(in), nxt;

	do {
		nxt = fgetc(in);
		//printf("decode: 58: %c\n", cur);
		int cnt = (nxt == EOF)?decoder->redund:8;
		for (; cnt; cur >>= 1, --cnt) {
			int t = cur & 1;
			//printf("decode: 61: %c", t+'0');
			//puts("");

			if (t == 0)
				p = p->l_child;
			else 
				p = p->r_child;

			if (!p->l_child && !p->r_child) {
				fputc(p->ch, out);
				//printf("decode: 72: %c\n", p->ch);
				p = decoder->root;
			} 
		}
		cur = nxt;
	} while (nxt != EOF); 
}
	
#undef T
