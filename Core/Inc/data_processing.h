#ifndef __DATA_PROCESSING_H_
#define __DATA_PROCESSING_H_

// 定义返回结构体
typedef struct {
    float data[4];  // 存储4个提取的浮点数
    uint8_t ok;     // 1: 解析成功，0: 失败
} ParsedFloats;

ParsedFloats parse_serial_floats(uint8_t* rx_buf, uint32_t max_len);

#endif
