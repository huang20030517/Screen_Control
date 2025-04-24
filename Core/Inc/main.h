/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define REMOTE_BUT_Pin GPIO_PIN_11
#define REMOTE_BUT_GPIO_Port GPIOE
#define STOP_BUT_Pin GPIO_PIN_9
#define STOP_BUT_GPIO_Port GPIOD
#define BACK_BUT_Pin GPIO_PIN_10
#define BACK_BUT_GPIO_Port GPIOD
#define UP_BUT_Pin GPIO_PIN_11
#define UP_BUT_GPIO_Port GPIOD
#define DOWN_BUT_Pin GPIO_PIN_12
#define DOWN_BUT_GPIO_Port GPIOD
#define FOR_BUT_Pin GPIO_PIN_13
#define FOR_BUT_GPIO_Port GPIOD
#define ENTER_BUT_Pin GPIO_PIN_14
#define ENTER_BUT_GPIO_Port GPIOD
#define SELECT_BUT_Pin GPIO_PIN_15
#define SELECT_BUT_GPIO_Port GPIOD
#define START_BUT_Pin GPIO_PIN_7
#define START_BUT_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
