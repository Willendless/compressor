#ifndef _DECODER_H
#define _DECODER_H
#include "huffman.h"
#include <stdio.h>
#define T Decoder_T
typedef struct Decoder *T;

T Decoder_new(FILE *);
void Decoder_decode(T, FILE *, FILE *);

#undef T
#endif
