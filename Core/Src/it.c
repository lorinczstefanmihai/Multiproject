/*
 * it.c
 *
 *  Created on: Feb 3, 2024
 *      Author: lorin
 */


#include "main.h"

extern UART_HandleTypeDef uart_gps;

void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

void USART1_IRQHandler (void)
{
	HAL_UART_IRQHandler(&uart_gps);
}
