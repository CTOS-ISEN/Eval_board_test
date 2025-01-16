/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "app_fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
#include <string.h>
#include <stdarg.h> //for va_list var arg functions
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

SPI_HandleTypeDef hspi2;

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
/* Definitions for ToFData_Queue */
osMessageQueueId_t ToFData_QueueHandle;
uint8_t ToFData_QueueBuffer[ 16 * sizeof( RANGING_SENSOR_Result_t ) ];
osStaticMessageQDef_t ToFData_QueueControlBlock;
const osMessageQueueAttr_t ToFData_Queue_attributes = {
  .name = "ToFData_Queue",
  .cb_mem = &ToFData_QueueControlBlock,
  .cb_size = sizeof(ToFData_QueueControlBlock),
  .mq_mem = &ToFData_QueueBuffer,
  .mq_size = sizeof(ToFData_QueueBuffer)
};
/* Definitions for LSM6DSOData_Queue */
osMessageQueueId_t LSM6DSOData_QueueHandle;
uint8_t LSM6DSOData_QueueBuffer[ 16 * sizeof( LSM6DSO_data ) ];
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
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USB_PCD_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM16_Init(void);
static void MX_SPI2_Init(void);
void StartDefaultTask(void *argument);
void StartAck_ToF_Data(void *argument);
void StartSendData(void *argument);
void StartAck_LSM6DSO_Data(void *argument);
void StartSendDataLSM6(void *argument);

/* USER CODE BEGIN PFP */
int _write(int file,char *ptr,int len);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int _write(int file, char *ptr, int len)
{
int DataIdx;
for (DataIdx = 0; DataIdx < len; DataIdx++)
{
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
  MX_SPI2_Init();
  if (MX_FATFS_Init() != APP_OK) {
    Error_Handler();
  }
  /* USER CODE BEGIN 2 */

  log_init(&huart1);
  //ToF_init();
  IKS01A3_MOTION_SENSOR_Init(IKS01A3_LSM6DSO_0, MOTION_GYRO);
    IKS01A3_MOTION_SENSOR_Init(1, MOTION_ACCELERO);

    IKS01A3_MOTION_SENSOR_Enable(IKS01A3_LSM6DSO_0, MOTION_GYRO);
    IKS01A3_MOTION_SENSOR_Enable(1, MOTION_ACCELERO);

      //IKS01A3_LIS2DW12_0;
      CalibrationLSM6DSO();
      HAL_TIM_Base_Start_IT(&htim16);
      HAL_TIM_Base_Start_IT(&htim2);


      log_printf("\r\n~ SD card demo by kiwih ~\r\n\r\n");

        HAL_Delay(1000); //a short delay is important to let the SD card settle

        //some variables for FatFs
        FATFS FatFs; 	//Fatfs handle
        FIL fil; 		//File handle
        FRESULT fres; //Result after operations

        //Open the file system
        fres = f_mount(&FatFs, "", 1); //1=mount now
        if (fres != FR_OK) {
        	log_printf("f_mount error (%i)\r\n", fres);
      	while(1);
        }

        //Let's get some statistics from the SD card
        DWORD free_clusters, free_sectors, total_sectors;

        FATFS* getFreeFs;

        fres = f_getfree("", &free_clusters, &getFreeFs);
        if (fres != FR_OK) {
        	log_printf("f_getfree error (%i)\r\n", fres);
      	while(1);
        }

        //Formula comes from ChaN's documentation
        total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
        free_sectors = free_clusters * getFreeFs->csize;

        log_printf("SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n", total_sectors / 2, free_sectors / 2);

        //Now let's try to open file "test.txt"
        fres = f_open(&fil, "test.txt", FA_READ);
        if (fres != FR_OK) {
        	log_printf("f_open error (%i)\r\n");
      	while(1);
        }
        log_printf("I was able to open 'test.txt' for reading!\r\n");

        //Read 30 bytes from "test.txt" on the SD card
        BYTE readBuf[30];

        //We can either use f_read OR f_gets to get data out of files
        //f_gets is a wrapper on f_read that does some string formatting for us
        TCHAR* rres = f_gets((TCHAR*)readBuf, 30, &fil);
        if(rres != 0) {
        	log_printf("Read string from 'test.txt' contents: %s\r\n", readBuf);
        } else {
        	log_printf("f_gets error (%i)\r\n", fres);
        }

        //Be a tidy kiwi - don't forget to close your file!
        f_close(&fil);

        //Now let's try and write a file "write.txt"
        fres = f_open(&fil, "write.txt", FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
        if(fres == FR_OK) {
        	log_printf("I was able to open 'write.txt' for writing\r\n");
        } else {
        	log_printf("f_open error (%i)\r\n", fres);
        }

        //Copy in a string
        strncpy((char*)readBuf, "a new file is made!", 19);
        UINT bytesWrote;
        fres = f_write(&fil, readBuf, 19, &bytesWrote);
        if(fres == FR_OK) {
        	log_printf("Wrote %i bytes to 'write.txt'!\r\n", bytesWrote);
        } else {
        	log_printf("f_write error (%i)\r\n");
        }

        //Be a tidy kiwi - don't forget to close your file!
        f_close(&fil);

        //We're done, so de-mount the drive
        f_mount(NULL, "", 0);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();
  /* Create the mutex(es) */
  /* creation of MutexSend */
  MutexSendHandle = osMutexNew(&MutexSend_attributes);

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
  /* creation of ToFData_Queue */
  ToFData_QueueHandle = osMessageQueueNew (16, sizeof(RANGING_SENSOR_Result_t), &ToFData_Queue_attributes);

  /* creation of LSM6DSOData_Queue */
  LSM6DSOData_QueueHandle = osMessageQueueNew (16, sizeof(LSM6DSO_data), &LSM6DSOData_Queue_attributes);

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
  while (1)
  {

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
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_MASTER;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 7;
  hspi2.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
  hspi2.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

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
  HAL_GPIO_WritePin(SD_CS_GPIO_Port, SD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD2_Pin|LD3_Pin|LD1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : SD_CS_Pin */
  GPIO_InitStruct.Pin = SD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SD_CS_GPIO_Port, &GPIO_InitStruct);

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
  for(;;)
  {
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

	static RANGING_SENSOR_Result_t result;
  /* Infinite loop */
  for(;;)
  {
	  osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
	  ToF_acquire_data(&result);
	        osMessageQueuePut(ToFData_QueueHandle, &result, 1, osWaitForever);
	      osDelay(1);

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
	static RANGING_SENSOR_Result_t result;
  /* Infinite loop */
  for(;;)
  {
	  osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
	  osMutexAcquire(MutexSendHandle, osWaitForever);
	  while(osMessageQueueGetCount(ToFData_QueueHandle)>0){

			osMessageQueueGet(ToFData_QueueHandle, &result, (uint8_t*) 1,osWaitForever);
			//print_result(&result);

			logger_print_result(&result);
		}
	  osMutexRelease(MutexSendHandle);

    osDelay(1);
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
  for(;;)
  {
		osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
		LSM6DSO_data mov_data;
		mov_data = InitLSM6DSO_Struct(mov_data);
		IKS01A3_MOTION_SENSOR_GetAxes(IKS01A3_LSM6DSO_0, MOTION_GYRO,
				&mov_data.axes_gyro);
		IKS01A3_MOTION_SENSOR_GetAxes(1, MOTION_ACCELERO, &mov_data.axes_acce);
		mov_data = CalibratedGet(mov_data);
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
  for(;;)
  {
		osThreadFlagsWait(1, osFlagsWaitAny, osWaitForever);
		osMutexAcquire(MutexSendHandle, osWaitForever);
		LSM6DSO_data send_data;
		while(osMessageQueueGetCount(LSM6DSOData_QueueHandle)>0) {
			send_data = InitLSM6DSO_Struct(send_data);
			osMessageQueueGet(LSM6DSOData_QueueHandle, &send_data, (uint8_t*) 1,
					osWaitForever);
			log_printf(
					"SEND : Xgyro: %ld | Ygyro: %ld | Zgyro: %ld | Xacc: %ld | Yacc: %ld | Zacc: %ld\n",
					send_data.axes_gyro.x, send_data.axes_gyro.y,
					send_data.axes_gyro.z, send_data.axes_acce.x,
					send_data.axes_acce.y, send_data.axes_acce.z);
		}
		printf("Send at : %ld\n", osKernelGetTickCount());
		osMutexRelease(MutexSendHandle);
		osDelay(1);
  }
  /* USER CODE END StartSendDataLSM6 */
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
			//osThreadFlagsSet(Ack_LSM6DSO_DatHandle, 1);
			//osThreadFlagsSet(Ack_ToF_DataHandle,1);

	}else if(htim->Instance == TIM2){
			//osThreadFlagsSet(SendDataLSM6Handle, 1);
			//osThreadFlagsSet(SendDataHandle, 1);
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
  while (1)
  {
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
