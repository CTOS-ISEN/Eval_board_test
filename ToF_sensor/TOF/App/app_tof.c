/**
 ******************************************************************************
 * @file          : app_tof.c
 * @author        : IMG SW Application Team
 * @brief         : This file provides code for the configuration
 *                  of the STMicroelectronics.X-CUBE-TOF1.3.4.2 instances.
 ******************************************************************************
 *
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_tof.h"
#include "main.h"
#include <stdio.h>

#include "app_tof_pin_conf.h"
#include "stm32wbxx_nucleo.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define TIMING_BUDGET (30U) /* 8 ms < TimingBudget < 200 ms */
#define POLLING_PERIOD (250U) /* refresh rate for polling mode (ms, shall be consistent with TimingBudget value) */

/* Private variables ---------------------------------------------------------*/
static RANGING_SENSOR_Capabilities_t Cap;
static RANGING_SENSOR_ProfileConfig_t Profile;
static RANGING_SENSOR_Result_t Result;
static int32_t status = 0;
static volatile uint8_t PushButtonDetected = 0;
volatile uint8_t ToF_EventDetected = 0;

/* Private function prototypes -----------------------------------------------*/
static void MX_53L4A2_SimpleRanging_Init(void);
static void MX_53L4A2_SimpleRanging_Process(RANGING_SENSOR_Result_t* result);
static int32_t decimal_part(float_t x);

void MX_TOF_Init(void) {
	/* USER CODE BEGIN SV */

	/* USER CODE END SV */

	/* USER CODE BEGIN TOF_Init_PreTreatment */

	/* USER CODE END TOF_Init_PreTreatment */

	/* Initialize the peripherals and the TOF components */

	MX_53L4A2_SimpleRanging_Init();

	/* USER CODE BEGIN TOF_Init_PostTreatment */

	/* USER CODE END TOF_Init_PostTreatment */
}

/*
 * LM background task
 */
void MX_TOF_Process(RANGING_SENSOR_Result_t* result) {
	/* USER CODE BEGIN TOF_Process_PreTreatment */

	/* USER CODE END TOF_Process_PreTreatment */

	MX_53L4A2_SimpleRanging_Process(result);

	/* USER CODE BEGIN TOF_Process_PostTreatment */

	/* USER CODE END TOF_Process_PostTreatment */
}

static void MX_53L4A2_SimpleRanging_Init(void) {
	uint32_t cal_distance_mm = 100; /* target distance used for offset calibration */
	/* Initialize Virtual COM Port */
	BSP_COM_Init(COM1);

	/* Initialize button */
	BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);

	/* reset XSHUT (XSDN) pin */
	HAL_GPIO_WritePin(VL53L4A2_XSHUT_C_PORT, VL53L4A2_XSHUT_C_PIN,
			GPIO_PIN_RESET);
	HAL_Delay(2);
	HAL_GPIO_WritePin(VL53L4A2_XSHUT_C_PORT, VL53L4A2_XSHUT_C_PIN,
			GPIO_PIN_SET);
	HAL_Delay(2);

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

static void MX_53L4A2_SimpleRanging_Process(RANGING_SENSOR_Result_t* result) {

	uint32_t Id;

	VL53L4A2_RANGING_SENSOR_ReadID(VL53L4A2_DEV_CENTER, &Id);
	VL53L4A2_RANGING_SENSOR_GetCapabilities(VL53L4A2_DEV_CENTER, &Cap);

//	Profile.RangingProfile = RS_MULTI_TARGET_MEDIUM_RANGE;
//	Profile.TimingBudget = TIMING_BUDGET;
//	Profile.Frequency = 0; /* Induces intermeasurement period, NOT USED for normal ranging */
//	Profile.EnableAmbient = 1; /* Enable: 1, Disable: 0 */
//	Profile.EnableSignal = 1; /* Enable: 1, Disable: 0 */

	/* set the profile if different from default one */
//	VL53L4A2_RANGING_SENSOR_ConfigProfile(VL53L4A2_DEV_CENTER, &Profile);
//
//	printf("--- OFFSET CALIBRATION ---\n");
//	printf("Please put a target at %lu mm\n", (unsigned long) cal_distance_mm);
//	printf("Press the user button to continue...\n");
//
//	/* wait until the button is pressed */
//	while (PushButtonDetected != 1)
//		;
//	PushButtonDetected = 0;
//
//	printf("--- BEGIN OFFSET CALIBRATION ---\n");
//	/* make sure that a target is placed at cal_distance_mm (100 mm is the default value in this example)
//	 * the application will perform some measure in order to have a log of some pre-calibration values
//	 */
//	status = VL53L4A2_RANGING_SENSOR_Start(VL53L4A2_DEV_CENTER,
//			RS_MODE_BLOCKING_CONTINUOUS);
//
//	if (status != BSP_ERROR_NONE) {
//		printf("VL53L4A2_RANGING_SENSOR_Start failed\n");
//		while (1)
//			;
//	}
//
//	/* Pre-calibration ranging */
//	for (i = 0; i < 10; i++) {
//		status = VL53L4A2_RANGING_SENSOR_GetDistance(VL53L4A2_DEV_CENTER,
//				&Result);
//
//		if (status == BSP_ERROR_NONE) {
//			print_result(&Result);
//		}
//
//		HAL_Delay(POLLING_PERIOD);
//	}
//
//	/* stop ranging and perform offset calibration */
//	VL53L4A2_RANGING_SENSOR_Stop(VL53L4A2_DEV_CENTER);
//	VL53L4A2_RANGING_SENSOR_OffsetCalibration(VL53L4A2_DEV_CENTER,
//			cal_distance_mm);
//	printf("--- END OF OFFSET CALIBRATION ---\n");

//	status = VL53L4A2_RANGING_SENSOR_Start(VL53L4A2_DEV_CENTER,
//			RS_MODE_BLOCKING_CONTINUOUS);
//
//	if (status != BSP_ERROR_NONE) {
//		printf("VL53L4A2_RANGING_SENSOR_Start failed\n");
//		while (1)
//			;
//	}

	status = VL53L4A2_RANGING_SENSOR_GetDistance(VL53L4A2_DEV_CENTER, result);
}

void print_result(RANGING_SENSOR_Result_t *Result) {
	uint8_t i;
	uint8_t j;

	for (i = 0; i < RANGING_SENSOR_MAX_NB_ZONES; i++) {
		printf("\nTargets = %lu",
				(unsigned long) Result->ZoneResult[i].NumberOfTargets);

		for (j = 0; j < Result->ZoneResult[i].NumberOfTargets; j++) {
			printf("\n |---> ");

			printf("Status = %ld, Distance = %5ld mm ",
					(long) Result->ZoneResult[i].Status[j],
					(long) Result->ZoneResult[i].Distance[j]);

			if (Profile.EnableAmbient)
				printf(", Ambient = %ld.%02ld kcps/spad",
						(long) Result->ZoneResult[i].Ambient[j],
						(long) decimal_part(Result->ZoneResult[i].Ambient[j]));

			if (Profile.EnableSignal)
				printf(", Signal = %ld.%02ld kcps/spad",
						(long) Result->ZoneResult[i].Signal[j],
						(long) decimal_part(Result->ZoneResult[i].Signal[j]));
		}
	}
	printf("\n");
}

static int32_t decimal_part(float_t x) {
	int32_t int_part = (int32_t) x;
	return (int32_t) ((x - int_part) * 100);
}

void BSP_PB_Callback(Button_TypeDef Button) {
	PushButtonDetected = 1;
}

#ifdef __cplusplus
}
#endif
