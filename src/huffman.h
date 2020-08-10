#ifndef _HUFFMAN_H
#define _HUFFMAN_H

typedef struct node{
		char ch;
		int weight;
		int len;
		char *code;
		struct node *l_child, *r_child;
}Node, *HuffmanTree;

typedef struct {
		char ch;
		char *code;
} HuaffmanCode, *HuffmanCode_table;

int create(HuffmanTree *root, int *wet, int n);
void release_tree(HuffmanTree root);
int code(HuffmanCode_table code_table, HuffmanTree root, int n);
void release_code_table(HuffmanCode_table, int len);
#endif
