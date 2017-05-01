#include "stm32f10x_conf.h"


#include "uart.h"
#include "systick.h"
#include <stdio.h>
#include <string.h>
#include "data_handle.h"
#include "queue.h"

#include "delay.h"


void test_io(void);

CycQueue *q = NULL;



int main(void)
{

	q = CycQueueInit();
	
	if(q == NULL)
	{
		//printf("malloc error!\n");
	}
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	delay_init(72);
	uart2_init();
	uart3_init();

	
	while(1)
	{
		
		frame_data_prase();
//		delay_ms(1000);
	}


}


/*
 * test led
 *
 */
void test_io(void)
{

	GPIO_InitTypeDef Gpio_InitStr;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	
	Gpio_InitStr.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	Gpio_InitStr.GPIO_Mode = GPIO_Mode_Out_PP;
	Gpio_InitStr.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &Gpio_InitStr);
	
	Gpio_InitStr.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init(GPIOC, &Gpio_InitStr);

	GPIO_ResetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
	GPIO_ResetBits(GPIOC,GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);
	
	//GPIO_SetBits(GPIOA,GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
	//GPIO_SetBits(GPIOC,GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5);

}


