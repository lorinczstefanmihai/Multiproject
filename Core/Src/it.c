/*
 * it.c
 *
 *  Created on: Feb 3, 2024
 *      Author: lorin
 */


#include "main.h"


void SysTick_Handler (void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
