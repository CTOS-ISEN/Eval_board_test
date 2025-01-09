/*
 * MEMS_library.h
 *
 *  Created on: Dec 9, 2024
 *      Author: reppl
 */

#ifndef MEMS_LIBRARY_MEMS_LIBRARY_H_
#define MEMS_LIBRARY_MEMS_LIBRARY_H_

#include <stdio.h>
#include "lsm6dso.h"
#include "stm32wbxx_nucleo_bus.h"
#include "main.h"

typedef struct{
	LSM6DSO_Axes_t Acc;
	LSM6DSO_Axes_t Gyr;
}LSM6DSO_data;

#define LSM6DSO_I2C_BUS 0U
#define LSM6DSO_I2C_ADD_H 0xD7
#define LSM6DSO_I2C_INIT BSP_I2C1_Init
#define LSM6DSO_I2C_DEINIT BSP_I2C1_DeInit
#define LSM6DSO_I2C_READ_REG BSP_I2C1_ReadReg
#define LSM6DSO_I2C_WRITE_REG BSP_I2C1_WriteReg
#define LSM6DSO_GET_TICK BSP_GetTick
#define LSM6DSO_DELAY HAL_Delay

void MyInitLSM6DSO(void);
void MyEnableLSM6DSO(void);
void MyGettingLSM6DSO(LSM6DSO_Axes_t *Acc, LSM6DSO_Axes_t *Gyr);

#endif /* MEMS_LIBRARY_MEMS_LIBRARY_H_ */
