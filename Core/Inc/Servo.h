#ifndef __SERVO_H_
#define __SERVO_H_

extern uint16_t Servo_base_pwm;
extern uint16_t Servo_up_pwm;

void Servo_Init(void);//¶æ»ú³õÊ¼»¯
void Servo_PWMRflash(uint16_t Servo_base_pwm,uint16_t Servo_up_pwm);
void Servo_PWMRflash_By_Angle(float pitch,float yaw);

#endif
