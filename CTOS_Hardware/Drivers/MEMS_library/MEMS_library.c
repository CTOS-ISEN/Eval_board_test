/*
 * MEMS_library.c
 *
 *  Created on: Dec 9, 2024
 *      Author: reppl
 */

#include "MEMS_library.h"

int32_t gyrxcalib = 0, gyrycalib = 0, gyrzcalib = 0, accxcalib = 0, accycalib = 0, acczcalib = 0;

void CalibrationLSM6DSO(){
	LSM6DSO_data calib_data;
	calib_data = InitLSM6DSO_Struct(calib_data);


	for(int i = 0; i<50; i++){
		IKS01A3_MOTION_SENSOR_GetAxes(IKS01A3_LSM6DSO_0, MOTION_GYRO, &calib_data.axes_gyro);
		IKS01A3_MOTION_SENSOR_GetAxes(1, MOTION_ACCELERO, &calib_data.axes_acce);
	}


	for(int i = 0; i<100; i++){
		IKS01A3_MOTION_SENSOR_GetAxes(IKS01A3_LSM6DSO_0, MOTION_GYRO, &calib_data.axes_gyro);
		IKS01A3_MOTION_SENSOR_GetAxes(1, MOTION_ACCELERO, &calib_data.axes_acce);
		gyrxcalib += calib_data.axes_gyro.x;
//		printf("%d : %ld\n", i, gyrxcalib);
		gyrycalib += calib_data.axes_gyro.y;
		gyrzcalib += calib_data.axes_gyro.z;
		accxcalib += calib_data.axes_acce.x;
		accycalib += calib_data.axes_acce.y;
		acczcalib += calib_data.axes_acce.z;
	}

	gyrxcalib = gyrxcalib/100;
	gyrycalib = gyrycalib/100;
	gyrzcalib = gyrzcalib/100;
	accxcalib = accxcalib/100;
	accycalib = accycalib/100;
	acczcalib = acczcalib/100;
	printf("%ld\n", gyrxcalib);
}

LSM6DSO_data InitLSM6DSO_Struct(LSM6DSO_data _struct){
	_struct.axes_acce.x = 0;
	_struct.axes_acce.y = 0;
	_struct.axes_acce.z = 0;
	_struct.axes_gyro.x = 0;
	_struct.axes_gyro.y = 0;
	_struct.axes_gyro.z = 0;
	return _struct;
}

LSM6DSO_data CalibratedGet(LSM6DSO_data mov_data){
	mov_data.axes_acce.x = mov_data.axes_acce.x - accxcalib;
	mov_data.axes_acce.y = mov_data.axes_acce.y - accycalib;
	mov_data.axes_acce.z = mov_data.axes_acce.z - acczcalib;
	mov_data.axes_gyro.x = mov_data.axes_gyro.x - gyrxcalib;
	mov_data.axes_gyro.y = mov_data.axes_gyro.y - gyrycalib;
	mov_data.axes_gyro.z = mov_data.axes_gyro.z - gyrzcalib;
	return mov_data;
}
