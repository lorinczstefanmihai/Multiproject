/*
 * main.c
 *
 *  Created on: Feb 3, 2024
 *      Author: lorin
 */


#include "stm32g0xx_hal.h"
#include "main.h"
#include "NMEA.h"
#include <stdio.h>
void UART_Init();
void Error_handler();

UART_HandleTypeDef console_output;
UART_HandleTypeDef uart_gps;




char data[550];

char start_console_message[30] = "---- STM32 RUNNNING ----";
char loading_console_message[40] = "GPS MODULE IS SEARCHING SIGNAL \n\r";

GPGGA_struct gpgga;

int main()
{
 	HAL_Init();
	UART_Init();

	HAL_UART_Transmit(&console_output,(uint8_t*)&start_console_message, 24, HAL_UART_TIMEOUT_VALUE);


	while(1)
	{
		HAL_UART_Receive_IT(&uart_gps,(uint8_t*)&data, 700);
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

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

	if(decode_NMEA_message(data, &gpgga) != FALSE)
	UART_GPS();
		//	HAL_UART_Transmit(&console_output, (uint8_t*)&data, 700, HAL_UART_TIMEOUT_VALUE);

}

void UART_GPS()
{
	char start_gps_message[13] = "GPS data: \n";
	char time_message[6] = "Time:";
	char latitude_message[12] = "\nLatitude:";
	char longitude_message[13] = "\nLongitude:";
	char nr_satttelites_message[24] = "\nNumber of satellites:";
	char altitude[12] = "\nAltitude:";

	char a[10], b[10];
	memset(a,'\0',12);
	memset(b,'\0',12);




	HAL_UART_Transmit(&console_output, start_gps_message, 12, HAL_UART_TIMEOUT_VALUE);

	HAL_UART_Transmit(&console_output, time_message, 6, HAL_UART_TIMEOUT_VALUE);

	sprintf(b, "%d", gpgga.time.hr);
	if(gpgga.time.hr < 10)
	{
		strcat(a,"0");
	}

	strcat(a,b);
	strcat(a,":");

	sprintf(b, "%d", gpgga.time.min);
	if(gpgga.time.min < 10)
	{
		strcat(a,"0");
	}

	strcat(a,b);
	strcat(a,":");

	sprintf(b, "%d", gpgga.time.sec);
	if(gpgga.time.sec < 10)
	{
		strcat(a,"0");
	}

	strcat(a,b);
	strcat(a,"\n");

	HAL_UART_Transmit(&console_output, a, strlen(a), HAL_UART_TIMEOUT_VALUE);

	//HAL_UART_Transmit(&console_output, latitude_message, 12, HAL_UART_TIMEOUT_VALUE);
	//HAL_UART_Transmit(&console_output, gpgga.location.latitude, 12, HAL_UART_TIMEOUT_VALUE);



}
