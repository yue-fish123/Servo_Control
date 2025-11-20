/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

extern UART_HandleTypeDef huart3;

/* USER CODE BEGIN Private defines */
#define MAX_RECV_LEN 300
#define USART1_MAX_RECV_LEN MAX_RECV_LEN

#define USART2_MAX_RECV_LEN MAX_RECV_LEN
	
typedef enum
{
	USART1_RX_STATE_START = 0U,
	USART1_RX_STATE_FINISH,
} USART1_RX_STATE;

typedef enum
{
	USART2_RX_STATE_START = 0U,
	USART2_RX_STATE_FINISH,
} USART2_RX_STATE;


extern uint8_t usart1_rx_len;
extern uint8_t usart1_rx_state;
extern uint8_t tmp_usart1_rx_buffer[USART1_MAX_RECV_LEN];
extern uint8_t g_usart1_rx_buff[USART1_MAX_RECV_LEN];

extern uint8_t usart2_rx_len;
extern uint8_t usart2_rx_state;
extern uint8_t tmp_usart2_rx_buffer[USART2_MAX_RECV_LEN];
extern uint8_t g_usart2_rx_buff[USART2_MAX_RECV_LEN];

/* USER CODE END Private defines */

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART3_UART_Init(void);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

