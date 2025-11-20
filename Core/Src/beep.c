#include "beep.h"
#include "main.h"

extern TIM_HandleTypeDef htim3;

// TIM4的计数频率
uint32_t timFrequency;
// 播放状态
uint8_t playState ;
// 播放进度
uint32_t playIndex ;
// 节拍速度(每分钟多少拍)
uint8_t bpm ;
// 每拍的持续时间
float noteDuration ;

//莫愁乡
  const Bate MoChouXiang[] = {
    // 我被困在了
    {M6, 1}, {M5, 1}, {M3, 1}, {M5, 0.5f}, {M5, 0.5f},
    // 这片混沌 柳暗
    {M6, 0.5f}, {M5, 1}, {M5, 0.5f}, {M3, 0.5f}, {M3, 0.5f}, {M3, 0.5f}, {M3, 0.5f},
    // 花明 一村一村一村
    {M2, 0.5f}, {M3, 0.5f}, {M5, 0.5f}, {M3, 0.5f}, {M2, 0.5f}, {M3, 0.5f}, {M5, 0.5f}, {M3, 0.5f},
    // 一村又一村
    {M2, 0.5f}, {M3, 0.5f}, {M3, 0.5f}, {L7, 0.5f}, {M3, 1}, {M1, 1},
    // 不能理顺我
    {M2, 1}, {M3, 1}, {M2, 1}, {M3, 0.5f}, {M3, 0.5f},
    
    // ......
    
    // 娃儿抬头望
    {M3, 0.5f}, {M2, 0.5f}, {M2, 0.5f}, {M3, 0.5f}, {M3, 0.5f}, {M2, 1.5f},
    // 姥姥在天上
    {M1, 0.5f}, {M3, 0.5f}, {M2, 0.5f}, {M3, 0.5f}, {M2, 1}, {M1, 1},
  };  

	const Bate Start_Music[]={
		{M1, 1}, {M2, 1}, {M3, 1}, {M1, 2}
	};
void Beep_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	// TIM4的计数频率
	timFrequency = TIM_GetCounterFreq(&htim3);
	// 播放状态
	playState = 1;
	// 播放进度
	playIndex = 0;
	// 节拍速度(每分钟多少拍)
	bpm = 132;
	// 每拍的持续时间
	noteDuration = 1000 * 60 / bpm;
}

void Beep_Off(void)
{
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);
}

/**
* 计算定时器计数频率
*/
uint32_t TIM_GetCounterFreq(TIM_HandleTypeDef *htim) {
    uint32_t timer_clock;
    // 高级定时器是APB2
    if (htim->Instance == TIM1) {
        timer_clock = HAL_RCC_GetPCLK2Freq();
        // 如果APB分频不为1，定时器时钟会翻倍
        if (HAL_RCC_GetPCLK2Freq() != (HAL_RCC_GetHCLKFreq() / 1)) {
            timer_clock *= 2;
        }
    } else {
      // 其他定时器是APB1
        timer_clock = HAL_RCC_GetPCLK1Freq();
        // 如果APB分频不为1，定时器时钟会翻倍
        if (HAL_RCC_GetPCLK1Freq() != (HAL_RCC_GetHCLKFreq() / 1)) {
            timer_clock *= 2;
        }
    }

    uint32_t prescaler = htim->Instance->PSC;
    return timer_clock / (prescaler + 1);
}

void Beep_Work(void){
	playState=1;
	while(playState==1){
      const Bate bate = Start_Music[playIndex];
      if (bate.frequency == P0) {
        // 休止符
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
      } else {
        // 将频率转换为计数值, 设置到自动重装载寄存器
        uint32_t arr = timFrequency / bate.frequency;
        __HAL_TIM_SET_AUTORELOAD(&htim3,arr);
        // 设置占空比为20%
        __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr / 5); // 20%占空比
        // 从0开始计数 重置PWM波形
        __HAL_TIM_SetCounter(&htim3, 0);
      }
      // 延时该音符的持续时间 (5ms的空白以区分连续两个相同的音符)
      HAL_Delay((uint32_t) (bate.period * noteDuration) - 5);
      __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
      HAL_Delay(5);

      // 下一个音符
      playIndex++;
      // 播放结束
      if (playIndex >=  sizeof(Start_Music) / sizeof(Bate)){
        playState = 0;
        playIndex = 0;
      }
	}
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);
}
