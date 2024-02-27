/*
 * NMEA.h
 *
 *  Created on: Feb 22, 2024
 *      Author: lorin
 */

#ifndef INC_NMEA_H_
#define INC_NMEA_H_

#include "main.h"


typedef struct
{
	uint8_t hr;
	uint8_t min;
	uint8_t sec;
}time_format;

typedef struct
{
	int latitude;
	char NS[2];
	int len_latitude_fractional_part;
	int longitude;
	char EW[2];
	int len_longitude_fractional_part;
}location_format;

typedef struct
{
	time_format time;
	location_format location;
	uint8_t fix_quality;
	int nr_of_satellites;
	int hdop;
	int altitude;
}GPGGA_struct;



bool decode_NMEA_message(char input_data[550], GPGGA_struct *gpgga);


#endif /* INC_NMEA_H_ */
