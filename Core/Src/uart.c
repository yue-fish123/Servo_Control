//#include "main.h"
//#include <string.h>  // 包含strtok函数的声明
//#include <stdlib.h>  // 包含atof函数的声明
//#include "stdio.h"

////extern uint8_t rx_buffer[1];
////extern uint16_t rx_len;  // 已接收的字符数
////extern uint8_t rx_complete;  // 接收完成标志（收到\r\n时置1）

//extern float x;
//extern float y;
//extern float w;
//extern float h;//目标的坐标以及框的长宽

//void divide_xywh(void){
//if (rx_complete) {
//        // 按逗号分割4个浮点数
//        char* token = strtok((char*)rx_buffer, ",");
//        if (token != NULL) x = atof(token);  // 转换x
//        
//        token = strtok(NULL, ",");
//        if (token != NULL) y = atof(token);  // 转换y
//        
//        token = strtok(NULL, ",");
//        if (token != NULL) w = atof(token);  // 转换w
//        
//        token = strtok(NULL, ",");
//        if (token != NULL) h = atof(token);  // 转换h

//        // 解析成功后，可在这里处理数据（比如调用Control函数）
//        // Control(x, y);

//        // 重置接收状态，准备下一次接收
//        rx_len = 0;
//        rx_complete = 0;
//        memset(rx_buffer, 0, sizeof(rx_buffer));
//        HAL_UART_Receive_IT(&huart2, &rx_buffer[rx_len], 1);
//    }
//}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
////  if (huart->Instance == USART2)  // 判断是USART2的中断
////  {
////     // 检测是否收到结束符\r\n（最后两个字符）
////    if (rx_len >= 1 && rx_buffer[rx_len-1] == '\r' && rx_buffer[rx_len] == '\n') {
////      rx_complete = 1;  // 标记接收完成
////      rx_buffer[rx_len+1] = '\0';  // 手动添加字符串结束符\0
////    } 
////		else {
////      rx_len++;  // 未完成，继续接收下一字节
////      // 防止缓冲区溢出（超过预设大小则重置）
////      if (rx_len >= sizeof(rx_buffer) - 1) {
////        rx_len = 0;
////      }
////		}
//////			divide_xywh();
//////			char buffer[50];
//////			int len = snprintf(buffer, sizeof(buffer), "%.2f,%.2f,%.2f,%.2f\r\n", x, y, w,h);
////			HAL_UART_Transmit(&huart1, (uint8_t*)rx_buffer, rx_len, HAL_MAX_DELAY);
////      HAL_UART_Receive_IT(&huart2, &rx_buffer[rx_len], 1);  // 继续使能中断
////  }
//////	if (huart->Instance == USART1)  // 判断是USART1的中断
//////  {
//////  }
//	    if (huart->Instance == USART2) {
////        // 1. 检查是否收到完整帧的结束符 \r\n
////        // （当前字节是\n，且前一个字节是\r，说明收到了完整的\r\n）
////        if (rx_len > 0 && rx_buffer[rx_len-1] == '\r' && rx_buffer[rx_len] == '\n') {
////            rx_complete = 1;  // 标记一帧数据接收完成
////            rx_buffer[rx_len-1] = '\0';  // 在\r的位置加结束符，截断\n
////        } else {
////            // 2. 未收到结束符，继续接收下一个字节
////            rx_len++;
////            // 防止缓冲区溢出（rx_buffer大小是100，预留1字节给结束符）
////            if (rx_len >= sizeof(rx_buffer) - 1) {
////                rx_len = 0;
////                memset(rx_buffer, 0, sizeof(rx_buffer));  // 溢出则重置
////            }
//            // 3. 重新开启中断，准备接收下1个字节（关键！）
//						
//            HAL_UART_Receive_IT(&huart2, rx_buffer,22);
//        //}
//    }
//}
