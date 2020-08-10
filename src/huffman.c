#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define MAX_NUM 100001

//小根堆
static Node *heap[MAX_NUM];
static int tot;
static void up(int p)
{
		Node *tmp;
		while (p>1)
			if (heap[p]->weight<heap[p>>1]->weight) {
					tmp = heap[p];
					heap[p] = heap[p>>1];
					heap[p>>1] = tmp;
					p >>= 1;
			} else break;
}

static void down(int p)
{
		Node *tmp;
		int s=p*2;//left node
		while (s<=tot) {
			if (s<tot&&heap[s]->weight>heap[s+1]->weight) s++;
			if (heap[s]->weight<heap[p]->weight) {
					tmp=heap[s];
					heap[s]=heap[p];
					heap[p]=tmp;
					p=s, s<<=1;
			} else break;
		}
}
static void insert(Node *new)
{
		heap[++tot]=new;
		up(tot);
}
static Node *pop()
{
		Node *ret = heap[1];
		heap[1] = heap[tot--];
		down(1);
		return ret;
}

int create(HuffmanTree *root, int *wet, int n)
{
	assert(n < MAX_NUM);
	int i, cnt=0;
	Node *new, *a, *b;


	//initialize
	tot = 0;
	for (i = 0; i < n; i++) {
			if (!wet[i])
					continue;
			new = malloc(sizeof(Node));
			new->ch = i;
			new->weight = wet[i];
			new->l_child = new->r_child = NULL;
			insert(new);
			cnt++;
	}

	//build
	while (tot != 1){
			a = pop(), b = pop();
			new = malloc(sizeof(Node));
			new->weight = a->weight + b->weight;
			new->l_child = a;
			new->r_child = b;
			insert(new);
	}
	*root = heap[1];

	return 1;
}

/** for test		
static int tree_len(HuffmanTree root)
{
	if (!root->l_child && !root->r_child) return 1;
	int ans=0;
	if (root -> l_child) ans += tree_len(root->l_child);
	if (root -> r_child) ans += tree_len(root->r_child);
	return ans+1;
}*/

int code(HuffmanCode_table code_table, HuffmanTree root, int n)
{
	if (code_table == NULL) return -1;
	if (!root) return -1;

	//printf("tree_len: %d\n", tree_len(root));
	//构建队列，层次遍历
	Node **queue = malloc(((n<<1)-1)*(sizeof(Node*)));
	Node *cur,*l, *r;
	int head = 0, tail = -1, i=0;

	queue[++tail] = root;

	//根就是叶子节点
	if (!root->l_child && !root->r_child) {
			root->code = malloc(2*sizeof(char));
			root->len = 2;
			root->code[0]='0', root->code[1]='\0';
			code_table[i].ch = root->ch;
			code_table[i].code = malloc(root->len*sizeof(char));
			memcpy(code_table[i].code, root->code, root->len);
			return 1;
	}

	root -> code = malloc(sizeof(char));
	root -> code[0] = '\0';
	root -> len = 1;
	root -> ch = -1;
	while (tail >= head) {
			cur = queue[head++];
			l = cur -> l_child;
			r = cur -> r_child;

			if (l) {
					queue[++tail] = l;
					l->code = malloc((cur->len+1)*sizeof(char));
					memcpy(l->code, cur->code, cur->len-1);
					l->code[cur->len-1] = '0';
					l->code[cur->len] = '\0';
					l->len = cur->len+1;
					if (!(l->l_child)&&!(l->r_child)) {
							code_table[i].ch = l->ch;
							code_table[i].code = malloc(l->len*sizeof(char));
							memcpy(code_table[i].code, l->code, l->len);
							//printf("huffman 139:ch:%d  char: %s\n",code_table[i].ch, code_table[i].code);
							i++;
					} 
			}

			if (r) {
					queue[++tail] = r;
					r->code = malloc((cur->len+1)*sizeof(char));
					memcpy(r->code, cur->code, cur->len-1);
					r->code[cur->len-1] = '1';
					r->code[cur->len] = '\0';
					r->len = cur->len+1;
					if (!r->l_child&&!r->r_child) {
							code_table[i].ch = r->ch;
							code_table[i].code = malloc(n*sizeof(char));
							memcpy(code_table[i].code, r->code, r->len);
							//printf("huffman 154:ch:%d  char: %s\n",code_table[i].ch, code_table[i].code);
							i++;
					} 

			}

	}

	//释放队列
	free(queue);
	return 1;
}

static void release_code(HuffmanTree n)
{
	if (!n) free(n->code);
	if (n->l_child) release_code(n->l_child);
	if (n->r_child) release_code(n->r_child);
}

void release_tree(HuffmanTree root)
{
	if (!root) return;
	release_code(root);
	free(root);
}

void release_code_table(HuffmanCode_table t, int len)
{
	int i;
	for (i = 0; i < len; i++)
			free(t[i].code);
	free(t);
}
