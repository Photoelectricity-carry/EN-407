#include "tim.h"
#include "gpio.h"
#include "encnoder.h"
float Get_Speed()
{
    int16_t zj;
    float Speed = 0;
    zj = __HAL_TIM_GetCounter(&htim3);
    __HAL_TIM_SetCounter(&htim3, 0);
    Speed = (float)zj / (4 * 15 * 34) * 100 * 60;

    return Speed;
}

float Get_Angle()
{
    int16_t zj;
    float angle = 0;
    zj = TIM2->CNT;
    angle = (float)zj / (4 * 15 * 34) * 360;
    return angle;
}



