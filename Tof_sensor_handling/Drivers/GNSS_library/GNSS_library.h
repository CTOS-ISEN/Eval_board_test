/*
 * GNSS_library.h
 *
 *  Created on: Jan 5, 2025
 *      Author: reppl
 */

#ifndef GNSS_LIBRARY_GNSS_LIBRARY_H_
#define GNSS_LIBRARY_GNSS_LIBRARY_H_

#include "logger.h"
#include "gnss_parser.h"
#include "gnss1a1_gnss.h"
#include "math.h"

void print_GPRMC(GNSSParser_Data_t *GNSS_Data_GPRMC);

#endif /* GNSS_LIBRARY_GNSS_LIBRARY_H_ */
