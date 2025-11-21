#include "main.h"
#include "Control.h"
#include "pca9685.h"

/************************************
*功能：使用定时器输出直接控制PWM舵机
*定时器：TIM1
*通道数量：2
*PWM输出范围：500到2500
*舵机输出角度：0到270度
**************************************/
uint16_t Servo_base_pwm;
uint16_t Servo_up_pwm;

uint16_t Servo_up_pwm_limit;

//舵机初始化
void Servo_Init(){
	Servo_base_pwm=1500;//给定底座舵机pwm初始值
	//Servo_up_pwm
	
	//Servo_up_pwm_limit=
}

//限制PWM的范围并设置（直接设置pwm）
void Servo_PWMRflash(uint16_t Servo_base_pwm,uint16_t Servo_up_pwm){
	if(Servo_base_pwm>=2500)	Servo_base_pwm=2500;
	else if(Servo_base_pwm<=500)	Servo_base_pwm=500;
	if(Servo_up_pwm>=2500)	Servo_up_pwm=2500;
	else if(Servo_up_pwm<=500)	Servo_up_pwm=500;
	
	TIM1->CCR1=Servo_base_pwm;
	TIM1->CCR4=Servo_up_pwm;
}

//通过输入角度直接控制舵机
void Servo_PWMRflash_By_Angle(float pitch,float yaw){
	int16_t Servo_base_pwm,Servo_up_pwm;
	Servo_base_pwm=(yaw/270)*2000+500;
	Servo_up_pwm=(pitch/270)*2000+500;
	TIM1->CCR1=Servo_base_pwm;
	TIM1->CCR4=Servo_up_pwm;
}

/****************************************
*功能：使用PCA9685控制PWM舵机
*控制舵机数量：8
*舵机输出角度：0到270度
*该部分包含以下几种功能：1.使用PS2手柄控制舵机的逻辑


*****************************************/

/****************************************
*功能：限制输出角度为正常范围
*****************************************/
void angle_limit(int16_t* angle){
	 if (angle == NULL) {
      return;
   }
	
	if(*angle<0) *angle=0;
	else if(*angle>270) *angle=270;
}
