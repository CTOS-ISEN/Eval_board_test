/*
 * MEMS_library.c
 *
 *  Created on: Dec 9, 2024
 *      Author: reppl
 */

#include "MEMS_library.h"

static LSM6DSO_Object_t lsm6dso_obj_0;

void MyInitLSM6DSO(void){
	LSM6DSO_IO_t io_ctx;
	io_ctx.BusType     = LSM6DSO_I2C_BUS;
	io_ctx.Address     = LSM6DSO_I2C_ADD_H;
	io_ctx.Init        = LSM6DSO_I2C_INIT;
	io_ctx.DeInit      = LSM6DSO_I2C_DEINIT;
	io_ctx.ReadReg     = LSM6DSO_I2C_READ_REG;
	io_ctx.WriteReg    = LSM6DSO_I2C_WRITE_REG;
	io_ctx.GetTick     = LSM6DSO_GET_TICK;
	io_ctx.Delay       = LSM6DSO_DELAY;

	LSM6DSO_RegisterBusIO(&lsm6dso_obj_0, &io_ctx);
	LSM6DSO_Init(&lsm6dso_obj_0);
}

void MyEnableLSM6DSO(void){
	LSM6DSO_ACC_Enable(&lsm6dso_obj_0);
	LSM6DSO_GYRO_Enable(&lsm6dso_obj_0);
}

void MyGettingLSM6DSO(LSM6DSO_Axes_t *Acc, LSM6DSO_Axes_t *Gyr){
	LSM6DSO_ACC_GetAxes(&lsm6dso_obj_0, Acc);
	LSM6DSO_GYRO_GetAxes(&lsm6dso_obj_0, Gyr);
	printf("______________________________________________________\n");
	printf("Gyr X : %ld | Gyr Y : %ld | Gyr Z : %ld\n", Gyr->x, Gyr->y, Gyr->z);
	printf("Acc X : %ld | Acc Y : %ld | Acc Z : %ld\n", Acc->x, Acc->y, Acc->z);
}
