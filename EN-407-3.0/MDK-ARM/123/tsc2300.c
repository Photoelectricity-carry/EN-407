#include "tim.h"
#include "tsc2300.h"
//#include "hal_flash.h"
#include "stm32f4xx.h" // Device header
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal.h"


//float R=0,G=0,B=0;
uint16_t Rgena,Ggena,Bgena;
uint16_t Ramount,Gamount,Bamount;
uint16_t amount = 0;
uint16_t d[3];
uint16_t s;
uint16_t y;
uint8_t red_flag;
uint8_t white_flag=0;
uint16_t x[3];

EXTI_HandleTypeDef l;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_4)
  {
      amount++;
  }
}
//void tcs3200_init(u8 s0,u8 s1)
//{

//	GPIO_InitTypeDef	GPIO_InitStructure;
//		
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PB�˿�ʱ��
//	
////	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
////	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
////	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
////	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//������+��
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO���ٶ�Ϊ50MHz
//	GPIO_Init(GPIOB, &GPIO_InitStructure);
//	S0=s0;
//	S1=s1;

//}
/*******************************************
*
*		  ��ƽ��
*
*******************************************/
void whitebalance(void)
{
//	EXTIX_Init();	//�ⲿ�жϳ�ʼ��
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
//	S2=0;S3=0;//��ɫͨ��
	amount=0;			 //��ʼ����
	HAL_Delay(10);
	Rgena = amount;   //�����ɫ����      
	amount=0;
	x[0]=Rgena;
//	STMFLASH_Write(0x08004000,(u16*)x[0],1);
//								 0x08000000
//----------------------------------
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
//	S2=1;S3=1;//��ɫͨ��
	amount=0;
	HAL_Delay(10);
	Ggena = amount;	 //�����ɫ����
	amount=0;
	x[1]=Ggena;
//	STMFLASH_Write(0x08004100,(u16*)x1[0],1);

//---------------------------------
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
//	S2=0;S3=1;//��ɫͨ��
	amount=0;
	HAL_Delay(10);
	Bgena = amount;	  //�����ɫ����
	amount=0;
	x[2]=Bgena;
//	STMFLASH_Write(0x08004000,(uint16_t*)x,3);
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
//	S2=1;S3=0;//�ر�ͨ��  


}  

uint16_t tcs2300_RED(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
//	S2=0;S3=0;
	amount=0;
	HAL_Delay(10);
	Ramount=(uint32_t) amount*255/x[0];	 //ȡRֵ
	if(Ramount>255) Ramount = 255;
	return Ramount;
//	amount=0;
}

uint16_t tcs2300_GREEN(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
//	S2=1;S3=1;
	amount=0;
	HAL_Delay(10);
	Gamount=(uint32_t) amount*255/x[1];	//ȡGֵ
	if(Gamount>255) Gamount = 255;
	return Gamount;
//	amount=0;
}

uint16_t tcs2300_BLUE(void)
{
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
//	S2=0;S3=1;
	amount=0;
	HAL_Delay(10);
	Bamount=(uint32_t) amount*255/x[2];//ȡBֵ
	if(Bamount>255) Bamount = 255;
	return Bamount;
//	amount=0;

}

	uint16_t rgb(void)
{
	float R=0,G=0,B=0;
	tcs2300_RED();
	tcs2300_GREEN();	  
	tcs2300_BLUE();	
	R=tcs2300_RED();
	G=tcs2300_GREEN();
	B=tcs2300_BLUE();
	
	if(R>G && R>B)//��ɫ
	{
		return 3;
	}
	if(G>R && G>B)//��ɫ
	{
		return 1;
	}
	if(B>G && B>R)//��ɫ
	{
		return 5;
	}
	if(R>220 && G>220 && B>220)//��ɫ
	{
		return 2;
	}
	if(R<80 && G<80 && B<80)//��ɫ
	{
		return 4;
	}
   else
	{
		return 0;
	}
}

void tsc2300(void)
{
	if(rgb() == 1)//��
	{
		car_go_left();
		HAL_Delay(500);
		Tracking();
		car_go_straight();
		HAL_Delay(500);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,1200);
		HAL_Delay(50);
		Tracking2();
	}
		if(rgb() == 2)//��
	{
		Tracking();
		car_go_straight();
		HAL_Delay(500);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,1200);
		HAL_Delay(50);
		Tracking2();
	}
		if(rgb() == 3)//��
	{
		car_go_right();
		HAL_Delay(500);
		Tracking();
		car_go_straight();
		HAL_Delay(500);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,1200);
		HAL_Delay(50);
		Tracking2();
	}
			if(rgb() == 4)//��
	{
		car_go_right();
		HAL_Delay(1000);
		Tracking();
		car_go_straight();
		HAL_Delay(500);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,1200);
		HAL_Delay(50);
		Tracking2();
	}
				if(rgb() == 5)//��
	{
		car_go_right();
		HAL_Delay(1500);
		Tracking();
		car_go_straight();
		HAL_Delay(500);
	__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_3,1200);
		HAL_Delay(50);
		Tracking2();
	}

		
}
