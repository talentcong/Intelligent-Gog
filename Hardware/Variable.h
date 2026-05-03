#ifndef _VARIABLE_H_
#define _VARIABLE_H_

typedef enum
{
    MODE_LIE_DOWN = 0,
    MODE_STAND = 1,
    MODE_SIT = 2,
    MODE_WALK = 3,
    MODE_WALKBACK = 4,
    MODE_JUMP_FORWARD = 5,
    MODE_JUMP_BACK = 6
} ActionMode_t;

typedef enum
{ 
    FACE_NORMAL = 0,
    FACE_HAPPY = 1,
    FACE_SLEEP = 2,
    FACE_VERY_HAPPY = 3
} FaceMode_t;

extern uint16_t RXData_Voice; 
extern ActionMode_t ActionMode;
extern FaceMode_t FaceMode;

#endif
