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
UART_HandleTypeDef uart_gps;


char data;

char start_console_message[30] = "---- STM32 RUNNNING ----";
char loading_console_message[40] = "GPS MODULE IS SEARCHING SIGNAL \n\r";

int main()
{
	HAL_Init();
	UART_Init();

	HAL_UART_Transmit(&console_output,(uint8_t*)&start_console_message, 24, HAL_UART_TIMEOUT_VALUE);


	while(1)
	{
		if(HAL_UART_Receive(&uart_gps,(uint8_t*)&data, 1, 100) == HAL_OK)
			HAL_UART_Transmit(&console_output, (uint8_t*)&data, 1, HAL_UART_TIMEOUT_VALUE);
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

	uart_gps.Instance = USART1;
	uart_gps.Init.BaudRate = 9600;
	uart_gps.Init.Mode = UART_MODE_TX_RX;
	uart_gps.Init.Parity = UART_PARITY_NONE;
	uart_gps.Init.StopBits = UART_STOPBITS_1;
	uart_gps.Init.WordLength = UART_WORDLENGTH_8B;
	uart_gps.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	if(HAL_UART_Init(&uart_gps) != HAL_OK)
	{
		Error_handler();
	}
}

void Error_handler()
{
	while(1);
}
