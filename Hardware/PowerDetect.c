#include "stm32f10x.h"                  // Device header
#include "PowerDetect.h"
#include "AD.h"
#include "Variable.h"

void PowerDetect_Init(void)
{
    AD_Init();

    //配置定时器3，每20ms进一次中断
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_TimeBaseStructure.TIM_Prescaler = 7199;        // 72MHz / 7200 = 10kHz
    TIM_TimeBaseStructure.TIM_Period = 199;             // 10kHz / 200 = 50Hz = 20ms
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM3, ENABLE);
}

//GetBattery，读取ADC值并换算为电池电量（单位：mV）
//AD_GetValue() 返回12位ADC值(0~4095)，经计算后转换为电压值并映射为电量
uint16_t GetBattery(void)
{
    float val = 3.3f * ((float)AD_GetValue() / 4096.0f) * 100.0f - 300.0f;
    if(val < 0) val = 0;
    Battery = (uint16_t)val;
    return Battery;
}

void GetAverage_Battery(void)
{
    if(++Battery_count<=100)
    {
        Battery_temp=GetBattery();
        Battery_temp_sum+=Battery_temp;
    }
    else
    {
        Average_Battery=Battery_temp_sum/100;
        Battery_count=0;
    }
}

