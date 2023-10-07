#include "motor.h"

extern int16_t set_speed_1;
extern int16_t set_speed_2;
//前进
void car_go_straight(void)
{
		set_speed_1 = 60;
		set_speed_2 = 60;
	 HAL_GPIO_WritePin(motor11_GPIO_Port,motor11_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port,motor12_Pin,GPIO_PIN_SET);
	 HAL_GPIO_WritePin(motor21_GPIO_Port,motor21_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port,motor22_Pin,GPIO_PIN_SET);
}
 
//右转
void car_go_right(void)
{
		set_speed_1 = 40;
		set_speed_2 = 40;
	 HAL_GPIO_WritePin(motor11_GPIO_Port,motor11_Pin,GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor12_GPIO_Port,motor12_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port,motor21_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port,motor22_Pin,GPIO_PIN_SET);

 
}
 
//左转
void car_go_left(void)
{
		set_speed_1 = 40;
		set_speed_2 = 40;
   HAL_GPIO_WritePin(motor11_GPIO_Port,motor11_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port,motor12_Pin,GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor21_GPIO_Port,motor21_Pin,GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor22_GPIO_Port,motor22_Pin,GPIO_PIN_RESET);
}
 
 
//停止
void car_go_ahead(void)
{
   HAL_GPIO_WritePin(motor11_GPIO_Port,motor11_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor12_GPIO_Port,motor12_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port,motor21_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor22_GPIO_Port,motor22_Pin,GPIO_PIN_RESET);
}
 
 
//后退
void car_go_after(void)
{
		set_speed_1 = 60;
		set_speed_2 = 60;
   HAL_GPIO_WritePin(motor11_GPIO_Port,motor11_Pin,GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor12_GPIO_Port,motor12_Pin,GPIO_PIN_RESET);
   HAL_GPIO_WritePin(motor21_GPIO_Port,motor21_Pin,GPIO_PIN_SET);
   HAL_GPIO_WritePin(motor22_GPIO_Port,motor22_Pin,GPIO_PIN_RESET);
 
}
