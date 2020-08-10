#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <assert.h>
#include "buffer.h"
#include "util.h"
#include "compressor.h"
#include "symtable.h"
#include "huffman.h"
#include "decoder.h"

void usage(char *program)
{
	printf("usage: %s -i input_file [-o output_name]\n", program);
	printf("-i	input_file	: text file for encoding\n");
	printf("-o	output_file	: name of encoded outputfile\n");
	printf("-d	decode_file	: name of decode outputfile\n");
	printf("-h	help\n");
}

int main(int argc, char *argv[])
{
	int i, j;
	int c, redund;
	int weight[SYMBOL_NUM];
	FILE *fp, *fout, *fdecode;
	char *ifile=NULL, *ofile=NULL, *dfile=NULL;
	data_buffer buf_table[SYMBOL_NUM];
	HuffmanTree root;
	HuffmanCode_table code_table;
	compressor comp;
	Decoder_T decoder;
	extern char *optarg;
	extern int optind;

	while ((c = getopt(argc, argv, "i:o:d:h")) != -1) {
			switch(c) {
			case 'i':
				ifile = optarg;
				printf("input file is %s\n",ifile);
				break;
			case 'o':
				ofile = optarg;
				printf("output file is %s\n", ofile);
				break;
			case 'h':
				usage(argv[0]);
				exit(1);
				break;
			case 'd':
				dfile = optarg;
				break;
			default:
				usage(argv[0]);
				break;
			}
	}

	if (ifile == NULL)
	{
		printf("Please input filename of encoding text\n");
		exit(1);
	}

	fp = fopen(ifile, "r");
	if (fp == NULL)
	{
		printf("Failed to open encoding text file %s\n", ifile);
		exit(1);
	}

	//1. 哈夫曼树构建
	memset(weight, 0, sizeof(weight));

	while ((c = getc(fp)) != EOF) {
			++weight[c];
	}
	
	
	if (create(&root, weight, SYMBOL_NUM) == -1) {
			printf("Failed to create HuffmanTree\n");
			exit(1);
	}

	code_table = malloc(SYMBOL_NUM*sizeof(HuaffmanCode));
	if (code(code_table, root, SYMBOL_NUM) == -1) {
			printf("Failed to create HuffmanCodeTable\n");
			exit(1);
	}
	

	//构造缓冲区列表
	for (i = 0; i < SYMBOL_NUM; i++) {
			if (!weight[i]) {
					clear_buf(&buf_table[i]);
					continue;
			}
			for (j = 0; j < SYMBOL_NUM; j++) {
					if (code_table[j].ch == i) {
							init_buf_by_code(&buf_table[i], code_table[j].code);
							redund += buf_table[i].len * weight[i];
							break;
					}
			}
	}


	//释放哈夫曼编码表空间
	release_code_table(code_table, SYMBOL_NUM);

	//2. 编码器初始化
	clear_buf(&comp.buf);
	init_symtable(&comp.symtable, buf_table);
	comp.root = root;
	

	//3. 编码及输出
	if (ofile != NULL)
		fout = fopen(ofile, "w");
	else {
		fout = fopen(ofile="./encode.out", "w");
		if (fout == NULL) {					
				printf("Failed to open/create output file\n");
				exit(1);
		}
		printf("output file is %s\n", ofile);
	}
	fseek(fp, 0L, SEEK_SET);

	//输出符号表到第一行
	fprintf(fout, "%d", redund % 8);
	for (i = 0; i < SYMBOL_NUM; i++) {
		if (comp.symtable.symbols[i].len > 0) {
			int len = comp.symtable.symbols[i].len;
			putc(' ', fout);
			for (j = 0; j < len; j++)
				putc(get_bit(&comp.symtable.symbols[i], j)+'0', fout);
			putc(' ', fout);
			fprintf(fout, "%d", i);
		}
	}
	putc('\n', fout);
	

	//数据编码
	int allB = 0;
	int allb = 0;
	int ch;
	printf("parsing ...\n");
	while ((ch = fgetc(fp)) != EOF) {
		allb += encode(&comp, ch, fout);
		allB++;
	}
	allb += flush(&comp, fout);
	printf("done.\n");
	printf("-input bytes: %d\n-output bytes: %f\n-compressed ratio: %f%%\n", allB, allb/8.0, allb/(allB*8.0)*100);

	assert(allb == redund);

	compressor_free(&comp);
	fclose(fout);
	fclose(fp);

	//数据解码
	if (dfile != NULL)
		fdecode = fopen(dfile, "w");
	else {
		fdecode = fopen(dfile="./decode.out", "w");
		if (fdecode == NULL) {					
				printf("Failed to open/create debug file\n");
				exit(1);
		}
	}
	printf("decode outputfile is %s\n", dfile);

	fout = fopen(ofile, "r");
	decoder = Decoder_new(fout);
	Decoder_decode(decoder, fout, fdecode);


	//文件指针关闭
	fclose(fdecode);
	fclose(fout);

	return 0;
}
