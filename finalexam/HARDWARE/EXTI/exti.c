#include "exti.h"
#include "delay.h"
#include "led.h"
#include "key.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F103������
//�ⲿ�ж���������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2019/9/17
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
int count = 0;
int redBlink = 0;
int yellowBlink = 0;

//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��
    __HAL_RCC_GPIOE_CLK_ENABLE();               //����GPIOEʱ��
    
    GPIO_Initure.Pin=GPIO_PIN_0;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //�����ش���
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
    
    GPIO_Initure.Pin=GPIO_PIN_3|GPIO_PIN_4; 	//PE3,4
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
    
    //�ж���0-PA0
    HAL_NVIC_SetPriority(EXTI0_IRQn,2,0);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);             //ʹ���ж���0
    
    //�ж���3-PE3
    HAL_NVIC_SetPriority(EXTI3_IRQn,2,2);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);             //ʹ���ж���2
    
    //�ж���4-PE4
    HAL_NVIC_SetPriority(EXTI4_IRQn,2,3);   	//��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);         	//ʹ���ж���4
}


//�жϷ�����
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);		//�����жϴ������ú���
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);		//�����жϴ������ú���
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);		//�����жϴ������ú���
}

//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(100);      //����
    switch(GPIO_Pin)
    {
			
		case GPIO_PIN_0:
        case GPIO_PIN_3:
        case GPIO_PIN_4:
					if(WK_UP == 1 | KEY1 == 0 | KEY0 == 0){
						if(count == 6) count = 1;
						switch(count){
						case 1:
							redBlink = 0;
							yellowBlink = 0;
							LED0 = 0;
							LED1 = 1;
							break;
						case 2:
							LED0 = 1;
							LED1 = 0;
							break;
						case 3:
							LED1 = 1;
							redBlink = 1;
							break;
						case 4:
							LED0 = 1;
							redBlink = 0;
							yellowBlink = 1;
							break;
						case 5:
							redBlink = 1;
							yellowBlink = 1;
							break;
						}
						count++;
				}
			}
}

