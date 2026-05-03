#include "stm32f10x.h"                  // Device header
#include "Variable.h"
#include "FaceConfig.h"
#include "OLED.h"
#include "OLED_Data.h"

void Face_Config(void)
{
    switch(FaceMode)
    {
        case FACE_NORMAL:
            OLED_Clear();
            OLED_ShowImage(0, 0, 128, 64, Face_eyes);
            break;
        case FACE_HAPPY:
            OLED_Clear();
            OLED_ShowImage(0, 0, 128, 64, Face_happy);
            break;
        case FACE_SLEEP:
            OLED_Clear();
            OLED_ShowImage(0, 0, 128, 64, Face_sleep);
            break;
        case FACE_VERY_HAPPY:
            OLED_Clear();
            OLED_ShowImage(0, 0, 128, 64, Face_very_happy);
            break;
        default:
            OLED_Clear();
            OLED_ShowImage(0, 0, 128, 64, Face_eyes);
            break;
    }

    /*电量处理*/
	if(Battery_Bit)
	{
		OLED_ShowString(0,0,"Power:",OLED_6X8);
		if(Average_Battety>=110) OLED_ShowString(36,0,"Charging",OLED_6X8);
		else if(Average_Battety>=100)OLED_ShowNum(36,0,Average_Battety,3,OLED_6X8);
		else OLED_ShowNum(36,0,Average_Battety,2,OLED_6X8);
	}

    OLED_Update();
}

