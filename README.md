# STM32_GPRS

## 1. 通信协议
详情参阅[《通信协议》](https://github.com/FanHongchuang/STM32_GPRS/wiki/%E9%80%9A%E4%BF%A1%E5%8D%8F%E8%AE%AE)
### 帧格式
|字段   |帧头    |帧长度 |命令标识|设备ID|端点ID    |帧数据 |校验和  |
|-------|-------|-------|-------|-------|-------|-------|-------|
|长度   |2字节   |1字节  |1字节  |1字节   |1字节   |n字节  |1字节   |

* 帧头     ：固定为0x5A 0xA5
* 帧长度   ：整帧的长度
* 命令标识 ：详情参阅《通信协议》第2章
* 设备ID ：设备唯一标识符
* 端点ID ：设备端点标识符
* 帧数据   ：帧数据长度为可变，详情参阅《通信协议》第3章
* 校验和   ：除去检验和字节本身，其余所有字节的累加和

## 2. Demo

```
/**
  * @brief  This demo describes how to set GPIO to output.
  * @param  None
  * @retval None
  */
static void set_gpio_output(void)
{

	GPIO_InitTypeDef Gpio_InitStr;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
	
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
```
```
/**
  * @brief  This demo describes how to read GPIO status.
  * @param  None
  * @retval None
  */
static void read_gpio_status(void)
{
	
	/* -1- Configure the pins */
	GPIO_InitTypeDef Gpio_InitStr;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	Gpio_InitStr.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	Gpio_InitStr.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &Gpio_InitStr);
	
	/* -2- Read the pin status you want */
    GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1);
	
	GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_4);
	
	GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_5);
}
```
```
/**
  * @brief  This demo describes how to configure GPIO interrupt.
  *         The interrupt handle function in the " stm32f10x_it.c ".
  * @param  None
  * @retval None
  */
static void gpio_interrupt_configure(void)
{
	/* -1- Configure the pins */
	EXTI_InitTypeDef   EXTI_InitStructure;
	GPIO_InitTypeDef   GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* -2- Connect EXTI2 Line to PD2 pin */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource2);

    /* -3- Configure EXTI2 line */
    EXTI_InitStructure.EXTI_Line = EXTI_Line2;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; // Trigger Rising 
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* -4- Enable and set EXTI2 Interrupt to the lowest priority */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
```
```
/**
  * @brief  This function handles External line 2 interrupt request.
  * @param  None
  * @retval None
  */
void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) == SET)
  {

    /* Clear the  EXTI line 0 pending bit */
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}
```

