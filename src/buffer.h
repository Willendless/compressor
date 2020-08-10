/**
 * buffer.h
 * 作用：
 * 1. 存储输出数据，缓冲区满或者flush()时进行输出
 * 2. 组成符号表的每一项
 */
#ifndef _BUFFER_H
#define _BUFFER_H

#define BUFFER_MAX_BITS 64
#define BUFFER_MAX_LEN 8 //缓冲区最大长度8字节
#define BITS_PER_BYTE 8  //每字节位数
#define BYTE_MASK 0xff	 //字节掩码

typedef struct {
	char databuf[BUFFER_MAX_LEN];
	int len;  
} data_buffer;

int init_buf_by_code(data_buffer *, char *code);	//由bit字符串构造缓冲区
void clear_buf(data_buffer *buf); //缓冲区初始化
data_buffer* insert(data_buffer *from, data_buffer *to); //将一个缓冲区插入到另一个缓冲区
void bufcpy(data_buffer *from, data_buffer *to);
int get_bit(data_buffer *buf, int p);

#endif
