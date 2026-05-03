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

    OLED_Update();
}

