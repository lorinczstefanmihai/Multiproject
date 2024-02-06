/*
 * main.c
 *
 *  Created on: Feb 3, 2024
 *      Author: lorin
 */


#include "stm32g0xx_hal.h"
#include "main.h"

void UART_Init();
void Error_handler();

UART_HandleTypeDef console_output;

int main()
{
	HAL_Init();
	UART_Init();

	char data[5] = "blaa\n\r";
	char iha;

	while(1)
	{
		HAL_UART_Transmit(&console_output, (uint8_t*)&data, 5, HAL_UART_TIMEOUT_VALUE);
	}

}

void UART_Init()
{
	console_output.Instance = USART2;
	console_output.Init.BaudRate = 115200;
	console_output.Init.Mode = UART_MODE_TX;
	console_output.Init.Parity = UART_PARITY_NONE;
	console_output.Init.StopBits = UART_STOPBITS_1;
	console_output.Init.WordLength = UART_WORDLENGTH_8B;
	console_output.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	if(HAL_UART_Init(&console_output) != HAL_OK)
	{
		Error_handler();
	}
}

void Error_handler()
{
	while(1);
}
