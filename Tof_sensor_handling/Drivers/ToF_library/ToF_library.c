/*
 * ToF_library.c
 *
 *  Created on: Dec 4, 2024
 *      Author: reppl
 */

#include "ToF_library.h"

static RANGING_SENSOR_ProfileConfig_t Profile;
RANGING_SENSOR_Result_t Result;
int32_t status = 0;

static int32_t decimal_part(float_t x);

void ToF_init(void){
	uint32_t cal_distance_mm = 100; /* target distance used for offset calibration */
	  	printf("CTOS ToF Sensor \n");

	  	//initialisation du sensor
	  	status = VL53L4A2_RANGING_SENSOR_Init(VL53L4A2_DEV_CENTER);

	  	/*if (status != BSP_ERROR_NONE)
	  	 {
	  	 printf("VL53L4A2_RANGING_SENSOR_Init failed\n");
	  	 while (1);
	  	 }*/
	  	Profile.RangingProfile = RS_MULTI_TARGET_MEDIUM_RANGE;
	  	Profile.TimingBudget = TIMING_BUDGET;
	  	Profile.Frequency = 0; /* Induces intermeasurement period, NOT USED for normal ranging */
	  	Profile.EnableAmbient = 1; /* Enable: 1, Disable: 0 */
	  	Profile.EnableSignal = 1; /* Enable: 1, Disable: 0 */

	  	//Configuration of the sensor
	  	status = VL53L4A2_RANGING_SENSOR_ConfigProfile(VL53L4A2_DEV_CENTER,&Profile);

	  	if (status != BSP_ERROR_NONE) {

	  		printf("VL53L4A2_RANGING_SENSOR_ConfigProfile failed with status %ld\n",status);
	  		Error_Handler();

	  	} else {

	  		printf("VL53L4A2_RANGING_SENSOR_ConfigProfile succeeded\n");
	  	}

	  	//Start the ToF sensor on the central board in blocking continuous mode
	  	status = VL53L4A2_RANGING_SENSOR_Start(VL53L4A2_DEV_CENTER,RS_MODE_BLOCKING_CONTINUOUS);

	  	if (status != BSP_ERROR_NONE) {
	  		printf("VL53L4A2_RANGING_SENSOR_Start failed\n");
	  		while (1)
	  			;
	  	}

	  	//Data collection for Calibration of the sensor
	  	for (int i = 0; i < 10; i++) {
	  		status = VL53L4A2_RANGING_SENSOR_GetDistance(VL53L4A2_DEV_CENTER,
	  				&Result);

	  		if (status == BSP_ERROR_NONE) {
	  			print_result(&Result);
	  		}

	  		HAL_Delay(POLLING_PERIOD);
	  	}
	  	VL53L4A2_RANGING_SENSOR_Stop(VL53L4A2_DEV_CENTER);
	  	//Calibration of the module using data collected during calibration period
	  	VL53L4A2_RANGING_SENSOR_OffsetCalibration(VL53L4A2_DEV_CENTER, cal_distance_mm);

	  	//Start the ToF sensor on the central board in blocking continuous mode
	  	status = VL53L4A2_RANGING_SENSOR_Start(VL53L4A2_DEV_CENTER, RS_MODE_BLOCKING_CONTINUOUS);

	  	//if error are detected a message is returned
	  	if (status != BSP_ERROR_NONE) {
	  		printf("VL53L4A2_RANGING_SENSOR_Start failed\n");
	  		while (1)
	  			;
	  	}
}

void ToF_acquire_data(RANGING_SENSOR_Result_t* result) {

	status = VL53L4A2_RANGING_SENSOR_GetDistance(VL53L4A2_DEV_CENTER, result);
	if(status != BSP_ERROR_NONE){
		Error_Handler();
	}
}


void print_result(RANGING_SENSOR_Result_t *Result)
{
  uint8_t i;
  uint8_t j;

  for (i = 0; i < RANGING_SENSOR_MAX_NB_ZONES; i++)
  {
    printf("\nTargets = %lu", (unsigned long)Result->ZoneResult[i].NumberOfTargets);

    for (j = 0; j < Result->ZoneResult[i].NumberOfTargets; j++)
    {
      printf("\n |---> ");

      printf("Status = %ld, Distance = %5ld mm ",
             (long)Result->ZoneResult[i].Status[j],
             (long)Result->ZoneResult[i].Distance[j]);

      if (Profile.EnableAmbient)
        printf(", Ambient = %ld.%02ld kcps/spad",
               (long)Result->ZoneResult[i].Ambient[j],
               (long)decimal_part(Result->ZoneResult[i].Ambient[j]));

      if (Profile.EnableSignal)
        printf(", Signal = %ld.%02ld kcps/spad",
               (long)Result->ZoneResult[i].Signal[j],
               (long)decimal_part(Result->ZoneResult[i].Signal[j]));
    }
  }
  printf("\n");
}

void logger_print_result(RANGING_SENSOR_Result_t *Result)
{
  uint8_t i;
  uint8_t j;

  for (i = 0; i < RANGING_SENSOR_MAX_NB_ZONES; i++)
  {
    log_printf("\nTargets = %lu", (unsigned long)Result->ZoneResult[i].NumberOfTargets);

    for (j = 0; j < Result->ZoneResult[i].NumberOfTargets; j++)
    {
      log_printf("\n |---> ");

      log_printf("Status = %ld, Distance = %5ld mm ",
             (long)Result->ZoneResult[i].Status[j],
             (long)Result->ZoneResult[i].Distance[j]);

      if (Profile.EnableAmbient)
        log_printf(", Ambient = %ld.%02ld kcps/spad",
               (long)Result->ZoneResult[i].Ambient[j],
               (long)decimal_part(Result->ZoneResult[i].Ambient[j]));

      if (Profile.EnableSignal)
        log_printf(", Signal = %ld.%02ld kcps/spad",
               (long)Result->ZoneResult[i].Signal[j],
               (long)decimal_part(Result->ZoneResult[i].Signal[j]));
    }
  }
  log_printf("\n");
}

static int32_t decimal_part(float_t x)
{
  int32_t int_part = (int32_t) x;
  return (int32_t)((x - int_part) * 100);
}
