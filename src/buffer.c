#include "buffer.h"
#include "util.h"
#include "compressor.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>


const unsigned int lowbitsmask[BITS_PER_BYTE+1] = { 0, 1, 3, 7, 15, 31, 63, 127, 255 };  //位级掩码，获取一个字节中对应位数据

//获取缓冲区字节数，向下取整
static int get_length_in_byte(data_buffer *buf)
{
	return buf->len / BITS_PER_BYTE;
}

//数据构造器：向缓冲区中插入1bit,失败则返回-1 
static int insert_bit(data_buffer *buf, int val)
{
	assert(val==0||val==1);
	int bytep = get_length_in_byte(buf);	//要插入的字节
	int bitp = buf->len-bytep*BITS_PER_BYTE;	//要插入字节的对应位
	if (buf -> len == BUFFER_MAX_BITS) return -1;
	buf->databuf[bytep] &= lowbitsmask[bitp];
	buf->databuf[bytep] |= (val<<bitp);
	buf->len++;
	return 1;
}
	
//数据选择器：从缓冲区中获取1bit,失败则返回-1
int get_bit(data_buffer *buf, int p)
{
	if (p >= buf->len) 	return -1;
	
	int bytep = p/BITS_PER_BYTE;
	int bitp = p-bytep*BITS_PER_BYTE;
	unsigned int tmp = buf->databuf[bytep];
	int ans = (tmp&lowbitsmask[bitp+1])>>bitp;

	assert(ans == 1 || ans == 0);
	return ans;
}


void clear_buf(data_buffer *buf)
{
	memset(buf->databuf, 0, BUFFER_MAX_LEN);
	buf->len = 0;
}

void bufcpy(data_buffer *from, data_buffer *to)
{
	to->len = from->len;
	memcpy(to, from, BUFFER_MAX_LEN);
}

//将一个缓冲区内容插入另一个缓冲区，若溢出则返回一个新缓冲区指针
data_buffer *insert(data_buffer *from, data_buffer *to)
{
	data_buffer *new_buf = NULL;

    //to缓冲区是满的
	if (to->len == BUFFER_MAX_BITS) { 
			new_buf = malloc(sizeof(data_buffer));
			bufcpy(from, new_buf);
			return new_buf;
	}

	//1. length modify
	if (to->len + from->len > BUFFER_MAX_BITS) {
			new_buf = malloc(sizeof(data_buffer));
			clear_buf(new_buf);
	}

	//2. data modify
	
	/**按位操作：**/
	int i, tmp;
	for (i = 0; i < from->len; i++) {
			tmp = get_bit(from, i);
			if (insert_bit(to, tmp) == -1)
				insert_bit(new_buf, tmp);
	}
	
	return new_buf;
}

int init_buf_by_code(data_buffer *buf, char *code)
{
	if (buf == NULL)
			return -1;
	if (*code == '\0')
			return -1;

	clear_buf(buf);
	for (; *code; code++) {
		assert(!*code || *code == '1' || *code == '0');
		switch (*code) {
		case '1': insert_bit(buf, 1); break;
		case '0': insert_bit(buf, 0); break;
		default: break;
		}
	}
	//printf("init_buf_by_code: %d\n",buf->len);

	return 1;
}

