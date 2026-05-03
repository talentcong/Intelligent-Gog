#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "PetAction.h"
#include "Delay.h"
#include "FaceConfig.h"
#include "Voiceinput.h"

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

