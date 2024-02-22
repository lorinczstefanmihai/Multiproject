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
	uint32_t time;
	float latitude;
	float longitude;
	uint8_t fix_quality;
	uint8_t nr_of_satellites;
	float hdop;
	float altitude;
}GPGGA_struct;


bool decode_NMEA_message(char input_data[550], GPGGA_struct *gpgga);


#endif /* INC_NMEA_H_ */
