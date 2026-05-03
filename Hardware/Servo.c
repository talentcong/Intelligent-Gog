#include "stm32f10x.h"                  // Device header
#include "Servo.h"
#include "PWM.h"


void Servo_Init(void)
{
    PWM_Init();
    Set_left_front_Angle(90);
    Set_left_back_Angle(90);
    Set_right_front_Angle(90);
    Set_right_back_Angle(90);
    }

void Set_left_front_Angle(float Angle)
{
    TIM_SetCompare1(TIM2,Angle/180*2000+500);
}
 
void Set_left_back_Angle(float Angle)
{
    TIM_SetCompare3(TIM2,Angle/180*2000+500);
}

void Set_right_front_Angle(float Angle)
{
    TIM_SetCompare2(TIM2,(180-Angle)/180*2000+500);
}

void Set_right_back_Angle(float Angle)
{
    TIM_SetCompare4(TIM2,(180-Angle)/180*2000+500);
}
