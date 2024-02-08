/*
 * msp.c
 *
 *  Created on: Feb 3, 2024
 *      Author: lorin
 */
#include "main.h"

void HAL_MspInit(void)
{
 //Here will do low level processor specific inits.
	//1. Set up the priority grouping of the arm cortex mx processor


	//2. Enable the required system exceptions of the arm cortex mx processor
	SCB->SHCSR |= 0x7 << 16; //usage fault, memory fault and bus fault system exceptions

}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
  GPIO_InitTypeDef gpio_uart;

  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART2_CLK_ENABLE();

  gpio_uart.Pin = GPIO_PIN_2;
  gpio_uart.Mode = GPIO_MODE_AF_PP;
  gpio_uart.Alternate = GPIO_AF1_USART2;
  gpio_uart.Pull = GPIO_PULLUP;
  gpio_uart.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &gpio_uart);


}
