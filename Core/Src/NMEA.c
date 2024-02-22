/*
 * NMEA.c
 *
 *  Created on: Feb 22, 2024
 *      Author: lorin
 */

#include "main.h"
#include "string.h"
#include "NMEA.h"
#include <stdio.h>


bool decode_NMEA_message(char input_data[550], GPGGA_struct *gpgga)
{
	int idx = 0, i = 0;
	char buffer[12];
	memset(buffer,'\0',12);

	while(input_data[idx] != 'G' || input_data[idx + 1] != 'P' || input_data[idx + 2] != 'G' || input_data[idx + 3] != 'G' || input_data[idx + 4] != 'A')
	{
		idx++;
		if(idx > 477)
			return FALSE;
	}

	idx += 6; // includem si virgula

	while(input_data[idx] != ',')
	{
		buffer[i] = input_data[idx];
		idx++;
		i++;
	}

	sscanf(buffer, "%d",(int*)&gpgga->time);
	i = 0;
	idx++;

	return TRUE;


}
