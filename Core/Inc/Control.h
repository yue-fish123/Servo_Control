#ifndef __CONTROL_H_
#define __CONTROL_H_

extern float x;
extern float y;
extern float w;
extern float h;

typedef enum{
	Servo_up,
	Servo_down
}Servo;

void Control(float x,float y);
void PID_Init(void);
void PTZ_Init(void);
int set_speed(Servo servo_n,float error);

#endif
