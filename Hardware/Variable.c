#include "stm32f10x.h"                  // Device header
#include "Variable.h"

uint16_t RXData_Voice = 0; //定义一个全局变量，用于存储接收到的语音数据

ActionMode_t ActionMode = MODE_STAND; //定义一个全局变量，用于存储当前的动作模式
FaceMode_t FaceMode = FACE_NORMAL; //定义一个全局变量，用于存储当前的表情模式
uint16_t Battery = 0; //定义一个全局变量，用于存储电池电量
uint16_t Battery_count = 0; //用于电池均值计数
uint16_t Battery_temp = 0; //临时存储单次电池采样值
uint32_t Battery_temp_sum = 0; //累加电池采样值
uint16_t Average_Battety = 0; //存储电池均值
uint8_t Battery_Bit = 0; //电池显示标志位

