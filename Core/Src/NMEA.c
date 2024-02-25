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
#include <math.h>

bool decode_NMEA_message(char input_data[550], GPGGA_struct *gpgga)
{
	int idx = 0, i = 0, integral_part, fractional_part, data;

	char buffer[12];
	memset(buffer,'\0',12);

	/******************* TIME DECODING *******************/

	while(input_data[idx] != 'G' || input_data[idx + 1] != 'P' || input_data[idx + 2] != 'G' || input_data[idx + 3] != 'G' || input_data[idx + 4] != 'A')
	{
		idx++;
		if(idx > 477)
			return FALSE;
	}

	idx += 6; // We also take in consideration the comma

	while(input_data[idx] != ',')
	{
		buffer[i] = input_data[idx];
		idx++;
		i++;
	}

	sscanf(buffer, "%d", &data);

	gpgga->time.hr = data / 10000;
	gpgga->time.min = ((data / 100) % 100);
	gpgga->time.sec = data % 100;

	memset(buffer,'\0',12);
 	i = 0; //reset the length counter
	idx++; //reach the first character of latitude value

	/******************* LATITUDE DECODING *******************/

	while(input_data[idx] != '.')
	{
		buffer[i] = input_data[idx];
		idx++;
		i++;
	}

	sscanf(buffer, "%d", &integral_part);
	i = 0;
	idx++; // pass the point
	memset(buffer,'\0',12);

	while(input_data[idx] != ',')
	{
		buffer[i] = input_data[idx];
		idx++;
		i++;
	}

	sscanf(buffer, "%d", &fractional_part);


	gpgga->location.latitude = integral_part *pow(10, strlen(buffer)) + fractional_part;

	idx++;

	gpgga->location.NS = input_data[idx];

	idx += 2; //reach the longitude

	/******************* LONGITUDE DECODING *******************/
	memset(buffer,'\0',12);
	i = 0;

	while(input_data[idx] != '.')
	{
		buffer[i] = input_data[idx];
		idx++;
		i++;
	}

	i = 0;
	idx++; // pass the point

	sscanf(buffer, "%d", &integral_part);
	memset(buffer, '\0', 12);

	while(input_data[idx] != ',')
	{
		buffer[i] = input_data[idx];
		idx++;
		i++;
	}

	sscanf(buffer, "%d", &fractional_part);


	gpgga->location.longitude = integral_part *pow(10, strlen(buffer)) + fractional_part;

	idx++;

	gpgga->location.EW = input_data[idx];

	idx += 2; //reach the fix quality

	memset(buffer,'\0',12);
	i = 0;

	/******************* Fix Quality DECODING *******************/

	sscanf(input_data[idx], "%d", &gpgga->fix_quality );

	if(gpgga->fix_quality < 1)
		return FALSE;

	idx += 2; //reach the number of satellites

	/******************* Number of satellites DECODING *******************/
	while(input_data[idx] != ',')
	{
		buffer[i] = input_data[idx];
		idx++;
		i++;
	}

	sscanf(buffer, "%d", &gpgga->nr_of_satellites );

	idx += 2;

	memset(buffer,'\0',12);
	i = 0;

	//get over next value, not needed
	while(input_data[idx] != ',')
	{
		idx++;
	}
	idx++;

	while(input_data[idx] != '.')
	{
		buffer[i] = input_data[idx];
		idx++;
		i++;
	}

	sscanf(buffer, "%d", &integral_part);
	idx++;

	sscanf(input_data[idx], "%d", &fractional_part);

	gpgga->altitude = integral_part * 10 + fractional_part;


	return TRUE;


}
