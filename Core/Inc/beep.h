#ifndef __BEEP_H
#define __BEEP_H

#include "main.h"

/*
音符频率
*/
#define P0 	0	// 休止符频率

#define L1 262  // 低音频率
#define L2 294
#define L3 330
#define L4 349
#define L5 392
#define L6 440
#define L7 494

#define M1 523  // 中音频率
#define M2 587
#define M3 659
#define M4 698
#define M5 784
#define M6 880
#define M7 988

#define H1 1047 // 高音频率
#define H2 1175
#define H3 1319
#define H4 1397
#define H5 1568
#define H6 1760
#define H7 1976
	
typedef struct
{
   uint16_t frequency; // 音符频率
   float period; // 音符持续时间，单位为拍
} Bate;

void Beep_Init(void);
void Beep_Off(void);
uint32_t TIM_GetCounterFreq(TIM_HandleTypeDef *htim);
void Beep_Work(void);

#endif
