#include "main.h"
#include "Servo.h"

extern float x;
extern float y;
extern float w;
extern float h;

float mid_x=640;//分辨率中值
float mid_y=360;

float error_x;//等于x与分辨率中值的差
float error_y;//等于y与分辨率中值的差
float p_yaw,i_yaw,d_yaw;//yaw角的pid参数
float p_pitch,i_pitch,d_pitch;//yaw角的pid参数
float old_error_x,old_error_y;
float yaw_integral;
float pitch_integral;

float yaw_derivative;
float pitch_derivative;

float yaw_integral_limit=200;

int Servo_speed_base;//底座舵机速度
int Servo_speed_up;//上层舵机速度

//云台舵机控制
void PID_Init(void){
	p_yaw=0.2;
	i_yaw=0;
	d_yaw=0;
	
	p_pitch=1;
	i_pitch=1;
	d_pitch=1;
	
	yaw_integral=0;
	pitch_integral=0;
	
	yaw_derivative=0;
	pitch_derivative=0;
}

void PTZ_Init(void){
	PID_Init();
	Servo_Init();
}

/*
舵机输出角度与CCR之间的关系：
CCR-------------角度
2500-------------270°
1500-------------135°
500--------------0°
*/
/*

分辨率设为1280*720
*/
uint8_t x_waiting_time=0;//x方向坐标不变的持续时间
uint8_t y_waiting_time=0;//y方向坐标不变的持续时间

typedef enum{
	Servo_up,
	Servo_down
}Servo;

int set_speed(Servo servo_n,float error){
	int Servo_speed=0;
	
	if(error<0){
		error=-error;
	}//取error绝对值
	
	if(error>600){
		Servo_speed=50;
	}
	else if(error<=600&&error>=400){
		Servo_speed=40;
	}
	else if(error<400&&error>=200){
		Servo_speed=35;
	}
	else if(error<200&&error>=0){
		Servo_speed=30;
	}
	return Servo_speed;
}

void Control(float x,float y){
	error_x=x-mid_x;
	error_y=y-mid_y;
	
	Servo_speed_base=set_speed(Servo_down,error_x);
	if(old_error_x-error_x){
		if(error_x>0){
			Servo_base_pwm-=Servo_speed_base;
		}
		else if(error_x<0){
			Servo_base_pwm+=Servo_speed_base;
		}
	}
//	else{
//		x_waiting_time++;
//		if(x_waiting_time>=150){
//			
//			x_waiting_time=0;
//		}
//	}
//	if(old_error_y-error_y!=0){
//		if(error_y>0){
//			Servo_up_pwm-=50;
//		}
//		else if(error_x<0){
//			Servo_up_pwm+=50;
//		}
//	}
	Servo_PWMRflash(Servo_base_pwm,Servo_up_pwm);
	
	old_error_x=error_x;
	old_error_y=error_y;
}
