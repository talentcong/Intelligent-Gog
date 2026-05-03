#include "stm32f10x.h"                  // Device header
#include "Servo.h"
#include "Variable.h"
#include "PetAction.h"
#include "Delay.h"

void PetAction_Init(void)
{
    Servo_Init();
}
//SetAll，用于同时设置四个舵机的角度
void SetAll(float lf, float lb, float rf, float rb)
{
    Set_left_front_Angle(lf);
    Set_left_back_Angle(lb);
    Set_right_front_Angle(rf);
    Set_right_back_Angle(rb);
}

//PetAction_Stand，用于让小狗站立
void PetAction_Stand(void)
{
    Set_left_front_Angle(90);
    Set_left_back_Angle(90);
    Set_right_front_Angle(90);
    Set_right_back_Angle(90);
}

//PetAction_Sit，用于让小狗坐下
void PetAction_Sit(void)
{
    Set_left_front_Angle(45);
    Set_left_back_Angle(0);
    Set_right_front_Angle(45);
    Set_right_back_Angle(0);
    Delay_ms(1000);
}

//PetAction_LieDown，用于让小狗躺下
void PetAction_LieDown(void)
{
    Set_left_front_Angle(0);
    Set_left_back_Angle(180);
    Set_right_front_Angle(0);
    Set_right_back_Angle(180);
}

//PetAction_Walk，用于让小狗行走
void PetAction_Walk(void)
{
    for(float a = 45; a <= 135; a += 3)
    {
        SetAll(a, 180 - a, 180 - a, a);
        Delay_ms(20);
    }

    for(float a = 135; a >= 45; a -= 3)
    {
        SetAll(a, 180 - a, 180 - a, a);
        Delay_ms(20);
    }
}


//PetAction_BackWalk，用于让小狗倒退
void PetAction_BackWalk(void)
{
    for(float a = 45; a <= 135; a += 3)
    {
        SetAll(180 - a, a, a, 180 - a);
        Delay_ms(20);
    }

    for(float a = 135; a >= 45; a -= 3)
    {
        SetAll(180 - a, a, a, 180 - a);
        Delay_ms(20);
    }
}

//PetAction_JumpForward，用于让小狗向前跳跃
void PetAction_JumpForward(void)
{
    // 蹲下蓄力
    SetAll(60, 120, 60, 120);
    Delay_ms(300);

    // 向前跳 — 四腿发力前跃
    SetAll(135, 45, 135, 45);
    Delay_ms(150);

    // 落地
    SetAll(90, 90, 90, 90);
    Delay_ms(200);
}

//PetAction_JumpBack，用于让小狗向后跳跃
void PetAction_JumpBack(void)
{
    // 蹲下蓄力
    SetAll(120, 60, 120, 60);
    Delay_ms(300);

    // 向后跳 — 四腿发力后跃
    SetAll(45, 135, 45, 135);
    Delay_ms(150);

    // 落地
    SetAll(90, 90, 90, 90);
    Delay_ms(200);
}



void PetAction_Perform(void)
{
    switch(ActionMode)
    {
        case MODE_LIE_DOWN:
        {
            PetAction_LieDown();
            break;
        }
        case MODE_STAND:
        {
            PetAction_Stand();
            break;
        }
        case MODE_SIT:
        {
            PetAction_Sit();
            break;
        }
        case MODE_WALK:
        {
            PetAction_Walk();
            break;
        }
        case MODE_WALKBACK:
        {
            PetAction_BackWalk();
            break;
        }
        case MODE_JUMP_FORWARD:
        {
            PetAction_JumpForward();
            break;
        }
        case MODE_JUMP_BACK:
        {
            PetAction_JumpBack();
            break;
        }
    }
}

void PetAction_Judgement(void)
{
    switch(RXData_Voice)
    {
        case 0x29://睡觉
        {
            ActionMode=MODE_LIE_DOWN;//设置当前动作模式为趴下
            FaceMode=FACE_SLEEP;//设置当前表情模式为睡觉
            break;
        }
        case 0x30://坐下
        {
            ActionMode=MODE_SIT;//设置当前动作模式为坐下
            FaceMode=FACE_HAPPY;//设置当前表情模式为高兴
            break;
        }
        case 0x31://站立 
        {
            ActionMode=MODE_STAND;//设置当前动作模式为站立
            FaceMode=FACE_NORMAL;//设置当前表情模式为正常
            break;
        }
        case 0x32://趴下
        {
            ActionMode=MODE_LIE_DOWN;//设置当前动作模式为趴下
            FaceMode=FACE_HAPPY;//设置当前表情模式为高兴
            break;
        }
        case 0x33://行走
        {
            ActionMode=MODE_WALK;//设置当前动作模式为行走
            FaceMode=FACE_VERY_HAPPY;//设置当前表情模式为非常高兴
            break;
        }
        case 0x34://倒退
        {
            ActionMode=MODE_WALKBACK;//设置当前动作模式为倒退
            FaceMode=FACE_HAPPY;//设置当前表情模式为高兴
            break;
        }
        case 0x41://向前跳
        {
            ActionMode=MODE_JUMP_FORWARD;
            FaceMode=FACE_VERY_HAPPY;
            break;
        }
        case 0x42://向后跳
        {
            ActionMode=MODE_JUMP_BACK;
            FaceMode=FACE_HAPPY;
            break;
        }
    }
}
