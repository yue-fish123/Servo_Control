#include <stdint.h>
#include <string.h>
#include <stdio.h>  // 用于sscanf

// 定义返回结构体
typedef struct {
    float data[4];  // 存储4个提取的浮点数
    uint8_t ok;     // 1: 解析成功，0: 失败
} ParsedFloats;

/**
 * @brief 从串口接收缓冲区中解析4个带2位小数的浮点数（格式："x.xx,y.yy,z.zz,w.ww\r\n"）
 * @param rx_buf: 接收缓冲区（uint8_t数组，如tmp_usart1_rx_buffer）
 * @param max_len: 缓冲区最大长度（USART1_MAX_RECV_LEN）
 * @return ParsedFloats: 解析结果及状态
 */
ParsedFloats parse_serial_floats(uint8_t* rx_buf, uint32_t max_len) {
    ParsedFloats res = {0};  // 初始化
    char* str = (char*)rx_buf;
    char* end;

    // 1. 检查缓冲区有效性
    if (rx_buf == NULL || max_len < 10) {  // 最短合法数据（如"0.00,0.00,0.00,0.00\r\n"约20字节）
        return res;
    }

    // 2. 定位末尾的"\r\n"，截断无效字符
    end = strstr(str, "\r\n");  // 查找回车换行符位置
    if (end == NULL) {
        return res;  // 未找到结束标志，格式错误
    }

    // 检查"\r\n"是否在缓冲区范围内（防止越界）
    if ((end - str) >= max_len) {
        return res;
    }

    // 3. 临时截断字符串（替换"\r"为结束符，避免解析换行符）
    *end = '\0';

    // 4. 用sscanf按格式严格解析4个浮点数（支持整数、小数形式）
    int parsed_count = sscanf(str, "%f,%f,%f,%f", 
                             &res.data[0], &res.data[1], &res.data[2], &res.data[3]);

    // 5. 恢复原缓冲区的"\r"（避免破坏原始数据）
    *end = '\r';

    // 6. 验证是否成功解析4个数据
    if (parsed_count == 4) {
        res.ok = 1;
    }

    return res;
}
