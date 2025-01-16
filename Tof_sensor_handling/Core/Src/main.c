/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim16;

UART_HandleTypeDef huart1;

PCD_HandleTypeDef hpcd_USB_FS;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 256 * 4
};
/* Definitions for Ack_ToF_Data */
osThreadId_t Ack_ToF_DataHandle;
const osThreadAttr_t Ack_ToF_Data_attributes = {
  .name = "Ack_ToF_Data",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for SendData */
osThreadId_t SendDataHandle;
const osThreadAttr_t SendData_attributes = {
  .name = "SendData",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 512 * 4
};
/* Definitions for Ack_LSM6DSO_Dat */
osThreadId_t Ack_LSM6DSO_DatHandle;
const osThreadAttr_t Ack_LSM6DSO_Dat_attributes = {
  .name = "Ack_LSM6DSO_Dat",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};
/* Definitions for SendDataLSM6 */
osThreadId_t SendDataLSM6Handle;
const osThreadAttr_t SendDataLSM6_attributes = {
  .name = "SendDataLSM6",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 256 * 4
};
/* Definitions for BackTaskGNSS */
osThreadId_t BackTaskGNSSHandle;
const osThreadAttr_t BackTaskGNSS_attributes = {
  .name = "BackTaskGNSS",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for ParserTaskGNSS */
osThreadId_t ParserTaskGNSSHandle;
const osThreadAttr_t ParserTaskGNSS_attributes = {
  .name = "ParserTaskGNSS",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for printGPRMC */
osThreadId_t printGPRMCHandle;
const osThreadAttr_t printGPRMC_attributes = {
  .name = "printGPRMC",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for printGPGGA */
osThreadId_t printGPGGAHandle;
const osThreadAttr_t printGPGGA_attributes = {
  .name = "printGPGGA",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};
/* Definitions for LSM6DSOData_Queue */
osMessageQueueId_t LSM6DSOData_QueueHandle;
uint8_t LSM6DSOData_QueueBuffer[ 16 * sizeof( IMU_Data ) ];
osStaticMessageQDef_t LSM6DSOData_QueueControlBlock;
const osMessageQueueAttr_t LSM6DSOData_Queue_attributes = {
  .name = "LSM6DSOData_Queue",
  .cb_mem = &LSM6DSOData_QueueControlBlock,
  .cb_size = sizeof(LSM6DSOData_QueueControlBlock),
  .mq_mem = &LSM6DSOData_QueueBuffer,
  .mq_size = sizeof(LSM6DSOData_QueueBuffer)
};
/* Definitions for MutexSend */
osMutexId_t MutexSendHandle;
const osMutexAttr_t MutexSend_attributes = {
  .name = "MutexSend"
};
/* Definitions for GNSSMutex */
osMutexId_t GNSSMutexHandle;
const osMutexAttr_t GNSSMutex_attributes = {
  .name = "GNSSMutex"
};
/* USER CODE BEGIN PV */
static GNSSParser_Data_t parsed_GNSSData;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM16_Init(void);
void StartDefaultTask(void *argument);
void StartAck_ToF_Data(void *argument);
void StartSendData(void *argument);
void StartAck_LSM6DSO_Data(void *argument);
void StartSendDataLSM6(void *argument);
void gnssBackground(void *argument);
void DataParserTask(void *argument);
void startPrintGPRMC(void *argument);
void startPrintGPGGA(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len) {
	int DataIdx;
	for (DataIdx = 0; DataIdx < len; DataIdx++) {
		//__io_putchar(*ptr++);
		ITM_SendChar(*ptr++);
	}
	return len;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* Configure the peripherals common clocks */
  PeriphCommonClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_PCD_Init();
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */
	log_init(&huart1);
	log_printf("\x1b[2J"); //clear screen
	log_printf("huart initialized\r\n");

	HAL_GPIO_WritePin(RST_GNSS_GPIO_Port, RST_GNSS_Pin, RESET);
	HAL_GPIO_WritePin(WKP_GNSS_GPIO_Port, WKP_GNSS_Pin, SET);
	log_init(&huart1);

	MyInitLSM6DSO();
	MyEnableLSM6DSO();
	MyInitLIS2MDL();
	MyEnableLIS2MDL();

	HAL_TIM_Base_Start_IT(&htim16);
	HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of MutexSend */
  MutexSendHandle = osMutexNew(&MutexSend_attributes);

  /* creation of GNSSMutex */
  GNSSMutexHandle = osMutexNew(&GNSSMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of LSM6DSOData_Queue */
  LSM6DSOData_QueueHandle = osMessageQueueNew (16, sizeof(IMU_Data), &LSM6DSOData_Queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of Ack_ToF_Data */
  Ack_ToF_DataHandle = osThreadNew(StartAck_ToF_Data, NULL, &Ack_ToF_Data_attributes);

  /* creation of SendData */
  SendDataHandle = osThreadNew(StartSendData, NULL, &SendData_attributes);

  /* creation of Ack_LSM6DSO_Dat */
  Ack_LSM6DSO_DatHandle = osThreadNew(StartAck_LSM6DSO_Data, NULL, &Ack_LSM6DSO_Dat_attributes);

  /* creation of SendDataLSM6 */
  SendDataLSM6Handle = osThreadNew(StartSendDataLSM6, NULL, &SendDataLSM6_attributes);

  /* creation of BackTaskGNSS */
  BackTaskGNSSHandle = osThreadNew(gnssBackground, NULL, &BackTaskGNSS_attributes);

  /* creation of ParserTaskGNSS */
  ParserTaskGNSSHandle = osThreadNew(DataParserTask, NULL, &ParserTaskGNSS_attributes);

  /* creation of printGPRMC */
  printGPRMCHandle = osThreadNew(startPrintGPRMC, NULL, &printGPRMC_attributes);

  /* creation of printGPGGA */
  printGPGGAHandle = osThreadNew(startPrintGPGGA, NULL, &printGPGGA_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
	/* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Macro to configure the PLL multiplication factor
  */
  __HAL_RCC_PLL_PLLM_CONFIG(RCC_PLLM_DIV1);

  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_MSI);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSICalibrationValue = RCC_MSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK4|RCC_CLOCKTYPE_HCLK2
                              |RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK2Divider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLK4Divider = RCC_SYSCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief Peripherals Common Clock Configuration
  * @retval None
  */
void PeriphCommonClock_Config(void)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SMPS;
  PeriphClkInitStruct.SmpsClockSelection = RCC_SMPSCLKSOURCE_HSI;
  PeriphClkInitStruct.SmpsDivSelection = RCC_SMPSCLKDIV_RANGE0;

  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN Smps */

  /* USER CODE END Smps */
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 31999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 15999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM16 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM16_Init(void)
{

  /* USER CODE BEGIN TIM16_Init 0 */

  /* USER CODE END TIM16_Init 0 */

  /* USER CODE BEGIN TIM16_Init 1 */

  /* USER CODE END TIM16_Init 1 */
  htim16.Instance = TIM16;
  htim16.Init.Prescaler = 31999;
  htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim16.Init.Period = 999;
  htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim16.Init.RepetitionCounter = 0;
  htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM16_Init 2 */

  /* USER CODE END TIM16_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USB Initialization Function
  * @param None
  * @retval None
  */
static void MX_USB_PCD_Init(void)
{

  /* USER CODE BEGIN USB_Init 0 */

  /* USER CODE END USB_Init 0 */

  /* USER CODE BEGIN USB_Init 1 */

  /* USER CODE END USB_Init 1 */
  hpcd_USB_FS.Instance = USB;
  hpcd_USB_FS.Init.dev_endpoints = 8;
  hpcd_USB_FS.Init.speed = PCD_SPEED_FULL;
  hpcd_USB_FS.Init.phy_itface = PCD_PHY_EMBEDDED;
  hpcd_USB_FS.Init.Sof_enable = DISABLE;
  hpcd_USB_FS.Init.low_power_enable = DISABLE;
  hpcd_USB_FS.Init.lpm_enable = DISABLE;
  hpcd_USB_FS.Init.battery_charging_enable = DISABLE;
  if (HAL_PCD_Init(&hpcd_USB_FS) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USB_Init 2 */

  /* USER CODE END USB_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(RST_GNSS_GPIO_Port, RST_GNSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, WKP_GNSS_Pin|VL53L4CX_XSHUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD2_Pin|LD3_Pin|LD1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : RST_GNSS_Pin */
  GPIO_InitStruct.Pin = RST_GNSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(RST_GNSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : WKP_GNSS_Pin VL53L4CX_XSHUT_Pin */
  GPIO_InitStruct.Pin = WKP_GNSS_Pin|VL53L4CX_XSHUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin LD3_Pin LD1_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|LD3_Pin|LD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : B2_Pin */
  GPIO_InitStruct.Pin = B2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(B2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : B3_Pin */
  GPIO_InitStruct.Pin = B3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B3_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartAck_ToF_Data */
/**
 * @brief Function implementing the Ack_ToF_Data thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartAck_ToF_Data */
void StartAck_ToF_Data(void *argument)
{
  /* USER CODE BEGIN StartAck_ToF_Data */
	/* Infinite loop */
	for (;;) {
		osDelay(1000);
	}
  /* USER CODE END StartAck_ToF_Data */
}

/* USER CODE BEGIN Header_StartSendData */
/**
 * @brief Function implementing the SendData thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSendData */
void StartSendData(void *argument)
{
  /* USER CODE BEGIN StartSendData */
	/* Infinite loop */
	for (;;) {
		osDelay(1000);
	}
  /* USER CODE END StartSendData */
}

/* USER CODE BEGIN Header_StartAck_LSM6DSO_Data */
/**
 * @brief Function implementing the Ack_LSM6DSO_Dat thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartAck_LSM6DSO_Data */
void StartAck_LSM6DSO_Data(void *argument)
{
  /* USER CODE BEGIN StartAck_LSM6DSO_Data */
	/* Infinite loop */
	for (;;) {
		osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
		IMU_Data mov_data;
		MyGettingLSM6DSO(&(mov_data.Acc), &(mov_data.Gyr));
		MyGettingLIS2MDL(&(mov_data.Mag));
		/*printf(
				"Xgyro: %ld | Ygyro: %ld | Zgyro: %ld | Xacc: %ld | Yacc: %ld | Zacc: %ld\n",
				mov_data.axes_gyro.x, mov_data.axes_gyro.y,
				mov_data.axes_gyro.z, mov_data.axes_acce.x,
				mov_data.axes_acce.y, mov_data.axes_acce.z);
		printf("Get at : %ld\n", osKernelGetTickCount());*/
		osMessageQueuePut(LSM6DSOData_QueueHandle, &mov_data, 1, osWaitForever);
		osDelay(1);
	}
  /* USER CODE END StartAck_LSM6DSO_Data */
}

/* USER CODE BEGIN Header_StartSendDataLSM6 */
/**
 * @brief Function implementing the SendDataLSM6 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartSendDataLSM6 */
void StartSendDataLSM6(void *argument)
{
  /* USER CODE BEGIN StartSendDataLSM6 */
	/* Infinite loop */
	for (;;) {
		osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
		osMutexAcquire(MutexSendHandle, osWaitForever);
		IMU_Data send_data;
		while(osMessageQueueGetCount(LSM6DSOData_QueueHandle)>0) {
			osMessageQueueGet(LSM6DSOData_QueueHandle, &send_data, (uint8_t*) 1,
					osWaitForever);
			log_printf(
					"SEND : Xgyro: %ld | Ygyro: %ld | Zgyro: %ld | Xacc: %ld | Yacc: %ld | Zacc: %ld | Xmag: %ld | Ymag : %ld | Zmag : %ld\n\r",
					send_data.Gyr.x, send_data.Gyr.y,
					send_data.Gyr.z, send_data.Acc.x,
					send_data.Acc.y, send_data.Acc.z,
					send_data.Mag.x, send_data.Mag.y,
					send_data.Mag.z);
		}
		printf("Send at : %ld\n", osKernelGetTickCount());
		osMutexRelease(MutexSendHandle);
		osDelay(1);
	}
  /* USER CODE END StartSendDataLSM6 */
}

/* USER CODE BEGIN Header_gnssBackground */
/**
 * @brief Function implementing the BackTaskGNSS thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_gnssBackground */
void gnssBackground(void *argument)
{
  /* USER CODE BEGIN gnssBackground */
	/* Infinite loop */
	for (;;) {
//		osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
//		GNSS1A1_GNSS_BackgroundProcess(GNSS1A1_TESEO_LIV3F);
		osDelay(100);
	}
  /* USER CODE END gnssBackground */
}

/* USER CODE BEGIN Header_DataParserTask */
/**
 * @brief Function implementing the ParserTaskGNSS thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_DataParserTask */
void DataParserTask(void *argument)
{
  /* USER CODE BEGIN DataParserTask */
//	const GNSS1A1_GNSS_Msg_t *gnssMsg = NULL;
//	GNSSParser_Status_t status, check;
//
//	if (GNSS1A1_GNSS_Init(GNSS1A1_TESEO_LIV3F) != BSP_ERROR_NONE) {
//		__BKPT();
//	}
//
//	if (GNSS_PARSER_Init(&parsed_GNSSData) != GNSS_PARSER_OK) {
//		__BKPT();
//	}

	/* Infinite loop */
	for (;;) {
//		osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
//		printf("Dataparser \n");
//		gnssMsg = GNSS1A1_GNSS_GetMessage(GNSS1A1_TESEO_LIV3F);
//		if (gnssMsg == NULL) {
//			continue;
//		}
//
//		check = GNSS_PARSER_CheckSanity((uint8_t*) gnssMsg->buf, gnssMsg->len);
//
//		if (check != GNSS_PARSER_ERROR) {
//			for (int m = 0; m < NMEA_MSGS_NUM; m++) {
//				osMutexAcquire(GNSSMutexHandle, osWaitForever);
//				status = GNSS_PARSER_ParseMsg(&parsed_GNSSData, (eNMEAMsg) m,
//						(uint8_t*) gnssMsg->buf);
//				osMutexRelease(GNSSMutexHandle);
//
//				if ((status != GNSS_PARSER_ERROR)) {
//
//					//check distance, rise flag if to far
//					//peut etre passer la position du telephone en parametre pour savoir si c'est trop loin (bluetooth)
//					if (parsed_GNSSData.gpgga_data.valid == (uint8_t) VALID) {
//						osThreadFlagsSet(printGPGGAHandle, 0x00000001);
//					} else {
//						osThreadFlagsSet(printGPRMCHandle, 0x00000001);
//					}
//
//				}
//
//			}
//		}
//
//		GNSS1A1_GNSS_ReleaseMessage(GNSS1A1_TESEO_LIV3F, gnssMsg);

		osDelay(1000);
	}
  /* USER CODE END DataParserTask */
}

/* USER CODE BEGIN Header_startPrintGPRMC */
/**
 * @brief Function implementing the printGPRMC thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_startPrintGPRMC */
void startPrintGPRMC(void *argument)
{
  /* USER CODE BEGIN startPrintGPRMC */
	/* Infinite loop */
	for (;;) {
		/*  log_printf("UTC:\t\t\t\t[ %02d:%02d:%02d ]\n\r",
		 parsed_GNSSData.gprmc_data.utc.hh,
		 parsed_GNSSData.gprmc_data.utc.mm,
		 parsed_GNSSData.gprmc_data.utc.ss);
		 log_printf("Status:\t\t\t\t[ %c ]\t\t",
		 parsed_GNSSData.gprmc_data.status);

		 if (parsed_GNSSData.gprmc_data.status == (uint8_t) 'A') {
		 log_printf("-- Valid (reported in 2D and 3D fix conditions)\n\r");
		 } else if (parsed_GNSSData.gprmc_data.status == (uint8_t) 'V') {
		 log_printf("-- Warning (reported in NO FIX conditions)\n\r");
		 } else {
		 log_printf("-- Unknown status\n\r");
		 }

		 float64_t lat_mod = fmod(parsed_GNSSData.gprmc_data.xyz.lat, 100.0);
		 float64_t lon_mod = fmod(parsed_GNSSData.gprmc_data.xyz.lon, 100.0);

		 log_printf("Latitude:\t\t\t[ %.0f' %02d'' %c ]\n\r",
		 (parsed_GNSSData.gprmc_data.xyz.lat - lat_mod) / 100.0,
		 (int16_t) lat_mod, parsed_GNSSData.gprmc_data.xyz.ns);
		 log_printf("Longitude:\t\t\t[ %.0f' %02d'' %c ]\n\r",
		 (parsed_GNSSData.gprmc_data.xyz.lon - lon_mod) / 100.0,
		 (int16_t) lon_mod, parsed_GNSSData.gprmc_data.xyz.ew);
		 log_printf("Speed over ground (knots):\t[ %.01f ]\n\r",
		 parsed_GNSSData.gprmc_data.speed);
		 log_printf("Trackgood:\t\t\t[ %.01f ]\n\r",
		 parsed_GNSSData.gprmc_data.trackgood);

		 log_printf("Date (ddmmyy):\t\t\t[ %02d%02d%02d ]\n\r",
		 (int16_t) ((parsed_GNSSData.gprmc_data.date / 10000)),
		 (int16_t) ((parsed_GNSSData.gprmc_data.date / 100)
		 - (100 * (parsed_GNSSData.gprmc_data.date / 10000))),
		 (int16_t) (parsed_GNSSData.gprmc_data.date
		 - (100 * (parsed_GNSSData.gprmc_data.date / 100))));

		 log_printf("Magnetic Variation:\t\t[ %.01f ]\n\r",
		 parsed_GNSSData.gprmc_data.mag_var);

		 if ((parsed_GNSSData.gprmc_data.mag_var_dir != (uint8_t) 'E')
		 && (parsed_GNSSData.gprmc_data.mag_var_dir != (uint8_t) 'W')) {
		 log_printf("Magnetic Var. Direction:\t[ - ]\n\r");
		 } else {
		 log_printf("Magnetic Var. Direction:\t[ %c ]\n\r",
		 parsed_GNSSData.gprmc_data.mag_var_dir);
		 }

		 log_printf("\n\n\r");
		 */
		osDelay(1000);
	}
  /* USER CODE END startPrintGPRMC */
}

/* USER CODE BEGIN Header_startPrintGPGGA */
/**
 * @brief Function implementing the printGPGGA thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_startPrintGPGGA */
void startPrintGPGGA(void *argument)
{
  /* USER CODE BEGIN startPrintGPGGA */
	/* Infinite loop */
	for (;;) {
		/*  osThreadFlagsWait(0x00000001, 0, osWaitForever);
		 osMutexAcquire(GNSSMutexHandle, osWaitForever);

		 float64_t lat_mod = fmod(parsed_GNSSData.gpgga_data.xyz.lat, 100.0);
		 float64_t lon_mod = fmod(parsed_GNSSData.gpgga_data.xyz.lon, 100.0);

		 log_printf("UTC:\t\t\t[ %02d:%02d:%02d ]\n\r",
		 parsed_GNSSData.gpgga_data.utc.hh,
		 parsed_GNSSData.gpgga_data.utc.mm,
		 parsed_GNSSData.gpgga_data.utc.ss);

		 log_printf("Latitude:\t\t[ %.0f' %d'' %c ]\n\r",
		 (parsed_GNSSData.gpgga_data.xyz.lat - lat_mod) / 100.0,
		 (int16_t) lat_mod, parsed_GNSSData.gpgga_data.xyz.ns);

		 log_printf("Longitude:\t\t[ %.0f' %d'' %c ]\n\r",
		 (parsed_GNSSData.gpgga_data.xyz.lon - lon_mod) / 100.0,
		 (int16_t) lon_mod, parsed_GNSSData.gpgga_data.xyz.ew);

		 log_printf("Satellites locked:\t[ %d ]\n\r",
		 parsed_GNSSData.gpgga_data.sats);

		 log_printf("Position accuracy:\t[ %.1f ]\n\r",
		 parsed_GNSSData.gpgga_data.acc);

		 log_printf("Altitude:\t\t[ %.2f%c ]\n\r",
		 parsed_GNSSData.gpgga_data.xyz.alt,
		 (parsed_GNSSData.gpgga_data.xyz.mis + 32U));

		 log_printf("Geoid infos:\t\t[ %d%c ]\n\r",
		 parsed_GNSSData.gpgga_data.geoid.height,
		 parsed_GNSSData.gpgga_data.geoid.mis);
		 log_printf("Diff update:\t\t[ %d ]\n\r",
		 parsed_GNSSData.gpgga_data.update);

		 osMutexRelease(GNSSMutexHandle);
		 */
		osDelay(1000);
	}
  /* USER CODE END startPrintGPGGA */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM17 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
	if (htim->Instance == TIM16) {
		osThreadFlagsSet(Ack_LSM6DSO_DatHandle, 1);
		//osThreadFlagsSet(Ack_ToF_DataHandle,1);
		osThreadFlagsSet(BackTaskGNSSHandle, 1);

	} else if (htim->Instance == TIM2) {
		osThreadFlagsSet(SendDataLSM6Handle, 1);
		osThreadFlagsSet(SendDataHandle, 1);
		osThreadFlagsSet(ParserTaskGNSSHandle, 1);
	}
  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM17) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
