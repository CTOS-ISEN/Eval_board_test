/*
 * GNSS_library.c
 *
 *  Created on: Jan 5, 2025
 *      Author: reppl
 */
#include "GNSS_library.h"

void print_GPRMC(GNSSParser_Data_t *GNSS_Data_GPRMC) {

	log_printf("UTC:\t\t\t\t[ %02d:%02d:%02d ]\n\r", GNSS_Data_GPRMC->gprmc_data.utc.hh, GNSS_Data_GPRMC->gprmc_data.utc.mm, GNSS_Data_GPRMC->gprmc_data.utc.ss);
	log_printf("Status:\t\t\t\t[ %c ]\t\t", GNSS_Data_GPRMC->gprmc_data.status);

	if (GNSS_Data_GPRMC->gprmc_data.status == (uint8_t) 'A') {
		log_printf("-- Valid (reported in 2D and 3D fix conditions)\n\r");
	} else if (GNSS_Data_GPRMC->gprmc_data.status == (uint8_t) 'V') {
		log_printf("-- Warning (reported in NO FIX conditions)\n\r");
	} else {
		log_printf("-- Unknown status\n\r");
	}

	float64_t lat_mod = fmod(GNSS_Data_GPRMC->gprmc_data.xyz.lat, 100.0);
	float64_t lon_mod = fmod(GNSS_Data_GPRMC->gprmc_data.xyz.lon, 100.0);

	log_printf("Latitude:\t\t\t[ %.0f' %02d'' %c ]\n\r", (GNSS_Data_GPRMC->gprmc_data.xyz.lat - lat_mod) / 100.0, (int16_t) lat_mod, GNSS_Data_GPRMC->gprmc_data.xyz.ns);
	log_printf("Longitude:\t\t\t[ %.0f' %02d'' %c ]\n\r", (GNSS_Data_GPRMC->gprmc_data.xyz.lon - lon_mod) / 100.0, (int16_t) lon_mod, GNSS_Data_GPRMC->gprmc_data.xyz.ew);
	log_printf("Speed over ground (knots):\t[ %.01f ]\n\r",	GNSS_Data_GPRMC->gprmc_data.speed);
	log_printf("Trackgood:\t\t\t[ %.01f ]\n\r",	GNSS_Data_GPRMC->gprmc_data.trackgood);

	log_printf("Date (ddmmyy):\t\t\t[ %02d%02d%02d ]\n\r", (int16_t) ((GNSS_Data_GPRMC->gprmc_data.date / 10000)), (int16_t) ((GNSS_Data_GPRMC->gprmc_data.date / 100) - (100 * (GNSS_Data_GPRMC->gprmc_data.date / 10000))), (int16_t) (GNSS_Data_GPRMC->gprmc_data.date - (100 * (GNSS_Data_GPRMC->gprmc_data.date / 100))));

	log_printf("Magnetic Variation:\t\t[ %.01f ]\n\r", GNSS_Data_GPRMC->gprmc_data.mag_var);

	if ((GNSS_Data_GPRMC->gprmc_data.mag_var_dir != (uint8_t) 'E') && (GNSS_Data_GPRMC->gprmc_data.mag_var_dir != (uint8_t) 'W')) {
		log_printf("Magnetic Var. Direction:\t[ - ]\n\r");
	} else {
		log_printf("Magnetic Var. Direction:\t[ %c ]\n\r", GNSS_Data_GPRMC->gprmc_data.mag_var_dir);
	}

	log_printf("\n\n\r");

}
