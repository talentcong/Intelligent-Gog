#include "stm32f10x.h"                  // Device header
#include "Variable.h"

uint16_t RXData_Voice = 0; //定义一个全局变量，用于存储接收到的语音数据

ActionMode_t ActionMode = MODE_STAND; //定义一个全局变量，用于存储当前的动作模式
FaceMode_t FaceMode = FACE_NORMAL; //定义一个全局变量，用于存储当前的表情模式

