#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "exti.h"

extern int redBlink;
extern int yellowBlink;

int main(void)
{
    HAL_Init();                    	 	//��ʼ��HAL��    
    Stm32_Clock_Init(RCC_PLL_MUL9);   	//����ʱ��,72M
	delay_init(72);               		//��ʼ����ʱ����
	uart_init(115200);					//��ʼ������
	LED_Init();							//��ʼ��LED	
	KEY_Init();							//��ʼ������
	EXTI_Init();						//��ʼ���ⲿ�ж�
	
    while(1)
    {
			if(redBlink && yellowBlink){
					LED0 = !LED0;
					LED1 = !LED1;
				}
				else if(yellowBlink){
					LED1 = !LED1;
				}
				else if(redBlink){
					LED0 = !LED0;
				}
        delay_ms(1000);             	//ÿ��1s��ӡһ�� 
	}
}
