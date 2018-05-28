#ifndef OLIVIA_H
#define OLIVIA_H

typedef void DecodedBuffer(void * sender, unsigned char * buffer, int bufferlen);

/* 定义常量 */
#define MODE_OLIVIA_NONE		0
#define	MODE_OLIVIA_4_250		1
#define	MODE_OLIVIA_8_250		2
#define	MODE_OLIVIA_4_500		3
#define	MODE_OLIVIA_8_500		4
#define	MODE_OLIVIA_16_500		5
#define	MODE_OLIVIA_8_1000		6
#define	MODE_OLIVIA_16_1000		7
#define	MODE_OLIVIA_32_1000		8
#define	MODE_OLIVIA_64_2000		9


/* 创建Olivia编码器 */
void* initEncoder(int mode, double freq, bool reverse);

/* 创建Olivia解码器 */
void* initDecoder(int mode, double freq, bool reverse, DecodedBuffer *onDecodedChar = NULL);

/* 释放Olivia编解码器 */
int freeOlivia(void * olivia);

/* 开始用编码器进行编码 */
int encode(void * encoder, unsigned char * msg, int length);

/* 获取编码器编码后的音频数据 */
int process(void * encoder, short * buffer, int length);

/* 解码器解码 */
int decode(void * decoder, short * buffer, int length);

/* 重新设置编解码器参数 */
int reset(void * olivia, int mode, double freq, bool reverse);

#endif // OLIVIA_H
