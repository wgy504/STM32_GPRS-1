
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_conf.h"
#include "uart.h"
#include "systick.h"
#include <stdio.h>
#include "data_handle.h"
#include "queue.h"
#include "delay.h"
#include "rtc.h"

/* Private function prototypes -----------------------------------------------*/
/* Global variables ---------------------------------------------------------*/
CycQueue *q = NULL; 
extern __IO uint32_t TimeDisplay;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{

	q = CycQueueInit();
	
	if(q == NULL)
	{
		//printf("malloc error!\n");
	}
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	delay_init(72);
	uart1_init();
	uart3_init();
	rtc_init();

	while(1)
	{
		frame_data_prase();
//		delay_ms(1000);

		/* If 1s has been elapsed */
    if (TimeDisplay == 1)
    {
			printf("\n\r");
      /* Display current time */
      Time_Display(RTC_GetCounter());
      TimeDisplay = 0;
    }
	}
}

