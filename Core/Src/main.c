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

char message_gps_not_connected[31] = "GPS SATELLITE NOT CONNECTED \n";

char data[550];

char start_console_message[30] = "---- STM32 RUNNNING ---- \n";
char loading_console_message[40] = "GPS MODULE IS SEARCHING SIGNAL \n\r";

GPGGA_struct gpgga;

int main()
{
 	HAL_Init();
	UART_Init();

	HAL_UART_Transmit(&console_output,(uint8_t*)&start_console_message, 27, HAL_UART_TIMEOUT_VALUE);


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
	{
		UART_GPS();
	}
	else{
		HAL_UART_Transmit(&console_output, (uint8_t*)&message_gps_not_connected, 30, HAL_UART_TIMEOUT_VALUE);
	}
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

	char string[10], substring[10];
	memset(string,'\0',12);
	memset(substring,'\0',12);




	HAL_UART_Transmit(&console_output, start_gps_message, 12, HAL_UART_TIMEOUT_VALUE);

	HAL_UART_Transmit(&console_output, time_message, 6, HAL_UART_TIMEOUT_VALUE);

	sprintf(substring, "%d", gpgga.time.hr);
	if(gpgga.time.hr < 10)
	{
		strcat(string,"0");
	}

	strcat(string,substring);
	strcat(string,":");

	sprintf(substring, "%d", gpgga.time.min);
	if(gpgga.time.min < 10)
	{
		strcat(string,"0");
	}

	strcat(string,substring);
	strcat(string,":");

	sprintf(substring, "%d", gpgga.time.sec);
	if(gpgga.time.sec < 10)
	{
		strcat(string,"0");
	}

	strcat(string,substring);
	strcat(string,"\n");

	HAL_UART_Transmit(&console_output, string, strlen(string), HAL_UART_TIMEOUT_VALUE);

	//HAL_UART_Transmit(&console_output, latitude_message, 12, HAL_UART_TIMEOUT_VALUE);
	//HAL_UART_Transmit(&console_output, gpgga.location.latitude, 12, HAL_UART_TIMEOUT_VALUE);



}
