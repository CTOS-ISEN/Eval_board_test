/*
 * MEMS_library.h
 *
 *  Created on: Dec 9, 2024
 *      Author: reppl
 */

#ifndef MEMS_LIBRARY_MEMS_LIBRARY_H_
#define MEMS_LIBRARY_MEMS_LIBRARY_H_

#include "iks01a3_motion_sensors.h"
#include <stdio.h>


typedef struct LSM6DSO_DATA{
	IKS01A3_MOTION_SENSOR_Axes_t axes_gyro;
	IKS01A3_MOTION_SENSOR_Axes_t axes_acce;
} LSM6DSO_data;

LSM6DSO_data InitLSM6DSO_Struct(LSM6DSO_data _struct);
void CalibrationLSM6DSO();
LSM6DSO_data CalibratedGet(LSM6DSO_data mov_data);

#endif /* MEMS_LIBRARY_MEMS_LIBRARY_H_ */
