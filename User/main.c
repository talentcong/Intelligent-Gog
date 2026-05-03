#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PetAction.h"
#include "Delay.h"
#include "FaceConfig.h"
#include "Voiceinput.h"
#include "PowerDetect.h"

int main(void)
{
	OLED_Init(); 
	Voice_Init();
	PetAction_Init();

	OLED_Clear();
    OLED_ShowImage(0, 0, 128, 64, Face_eyes);
	OLED_Update();
	while(1)
	{
		Face_Config();
		PetAction_Perform();
	}
}

//TIM3中断服务函数，每20ms调用一次，用于电池电压均值采样
void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
        GetAverage_Battery();
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

