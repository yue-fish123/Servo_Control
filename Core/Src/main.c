/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Control.h"
#include "Servo.h"
#include "stdio.h"
#include "string.h"
#include <stdarg.h>
#include "data_processing.h"
#include "pca9685.h"
#include "PS2.h"
#include "beep.h"
#include "Bus_Servo.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
float x=0;
float y=0;
float w=0;
float h=0;

uint8_t usart1_rx_len = 0;
uint8_t usart1_rx_state = USART1_RX_STATE_START;
uint8_t tmp_usart1_rx_buffer[USART1_MAX_RECV_LEN] = {0};
uint8_t g_usart1_rx_buff[USART1_MAX_RECV_LEN] = {0};

uint8_t usart2_rx_len = 0;
uint8_t usart2_rx_state = USART2_RX_STATE_START;
uint8_t tmp_usart2_rx_buffer[USART2_MAX_RECV_LEN] = {0};
uint8_t g_usart2_rx_buff[USART2_MAX_RECV_LEN] = {0};

ParsedFloats result;

//JOYSTICK_TypeDef ps2;
//extern uint8_t PS2_data[9];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t BLE_DIRECT_Printf(const char *format, ...)
{
  char *buf; //= mymalloc(SRAMIN, 1024);
  va_list args;
  va_start(args, format);
  uint16_t len = vsprintf((char *)buf, (char *)format, args);
  va_end(args);

//#if Use_SECRET > 0
//  // 加密算法1
//  char *encryptedText = mymalloc(SRAMIN, len);
//  len = encrypt(buf, secret_key, encryptedText);
//  myfree(SRAMIN, buf);
//  // 加密算法2
//  char *encoded_data = mymalloc(SRAMIN, 4 * ((len + 2) / 3) + 1);
//  len = base64_encode((const uint8_t *)encryptedText, len, encoded_data);
//  myfree(SRAMIN, encryptedText);
//  HAL_UART_Transmit_DMA(&huart1, (u8 *)encoded_data, len); // 串口打印函数，可以更换为中断发送或者DMA发送
//  myfree(0, encoded_data);
//#else
  HAL_UART_Transmit_DMA(&huart1, (uint8_t *)buf, len); // 串口打印函数，可以更换为中断发送或者DMA发送
  //myfree(0, buf);
//#endif
  return 0;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_CAN_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_USART3_UART_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
	
	//PTZ_Init();
	 PCA_Servo_Init(50.0f, 135);
//	 PS2_Init();
	  PS2_SetInit();
	 //蜂鸣器启动音乐
//	 Beep_Init();
//	 Beep_Work();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
      PS2_ReadData();          //获取数据
		  
			HAL_Delay(1);
	  	char buffer[50];
			int len = snprintf(buffer, sizeof(buffer),"%5d %5d %5d %5d\r\n",PS2_AnologData(PSS_LX),PS2_AnologData(PSS_LY),
	      	                          PS2_AnologData(PSS_RX),PS2_AnologData(PSS_RY));
    
		HAL_UART_Transmit(&huart1, (uint8_t *)buffer, len, 100);
		PCA_Servo(7,map(PS2_AnologData(PSS_LX),0, 255, 0, 270));
//		HAL_UART_Transmit_DMA(&huart1, (uint8_t *)buffer, sizeof(buffer)); // 串口打印函数，可以更换为中断发送或者DMA发送
      PS2_ClearData();      //清除数据
    HAL_Delay(100);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
