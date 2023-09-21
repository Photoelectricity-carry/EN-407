#include "tim.h"
#include "gpio.h"
#include "motor.h"
float Get_Speed()
{
    int16_t zj,n;
    float Speed = 0;
    zj = TIM2->CNT;
 __HAL_TIM_SetCounter(&htim2, 0);
    Speed = ((float)zj*3.1415926*2*0.0334)/(0.00091*1350); /// (4 * 15 * 34) * 100 * 60;r=0.0334

// TIM2->CNT=0;
    return Speed;
}
float Get_Angle()
{
    int16_t zj;
    float angle = 0;
    zj = __HAL_TIM_GetCounter(&htim2);
    angle = ((float)zj / 1350)*360;
    return angle;
}
