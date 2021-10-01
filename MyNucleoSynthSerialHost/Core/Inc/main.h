/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f7xx_hal.h"
#include "stm32f7xx_ll_dac.h"
#include "stm32f7xx_ll_rcc.h"
#include "stm32f7xx_ll_bus.h"
#include "stm32f7xx_ll_system.h"
#include "stm32f7xx_ll_exti.h"
#include "stm32f7xx_ll_cortex.h"
#include "stm32f7xx_ll_utils.h"
#include "stm32f7xx_ll_pwr.h"
#include "stm32f7xx_ll_dma.h"
#include "stm32f7xx_ll_tim.h"
#include "stm32f7xx_ll_usart.h"
#include "stm32f7xx.h"
#include "stm32f7xx_ll_gpio.h"
#include <stdio.h>

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

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
/* USART3 instance is used. (TX on PD.08, RX on PD.09) */
#define USARTx_INSTANCE               USART3
#define USARTx_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3)
#define USARTx_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1)
#define USARTx_IRQn                   USART3_IRQn
#define USARTx_IRQHandler             USART3_IRQHandler

#define USARTx_GPIO_CLK_ENABLE()      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD)   /* Enable the peripheral clock of GPIOD */
#define USARTx_TX_PIN                 LL_GPIO_PIN_8
#define USARTx_TX_GPIO_PORT           GPIOD
#define USARTx_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_8, LL_GPIO_AF_7)
#define USARTx_RX_PIN                 LL_GPIO_PIN_9
#define USARTx_RX_GPIO_PORT           GPIOD
#define USARTx_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_8_15(GPIOD, LL_GPIO_PIN_9, LL_GPIO_AF_7)
#define APB_Div 4

/* USART2 instance is used. (TX on PD.05, RX on PD.06)
   (requires wiring USART2 TX/Rx Pins to USB to UART adapter) */
#define USARTy_INSTANCE               USART2
#define USARTy_CLK_ENABLE()           LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2)
#define USARTy_CLK_SOURCE()           LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1)
#define USARTy_IRQn                   USART2_IRQn
#define USARTy_IRQHandler             USART2_IRQHandler

#define USARTy_GPIO_CLK_ENABLE()      LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOD)   /* Enable the peripheral clock of GPIOD */
#define USARTy_TX_PIN                 LL_GPIO_PIN_5
#define USARTy_TX_GPIO_PORT           GPIOD
#define USARTy_SET_TX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOD, LL_GPIO_PIN_5, LL_GPIO_AF_7)
#define USARTy_RX_PIN                 LL_GPIO_PIN_6
#define USARTy_RX_GPIO_PORT           GPIOD
#define USARTy_SET_RX_GPIO_AF()       LL_GPIO_SetAFPin_0_7(GPIOD, LL_GPIO_PIN_6, LL_GPIO_AF_7)
#define APB_Div 4

/* Definition for DACx clock resources */
#define DACx                            DAC
#define DACx_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define DMAx_CLK_ENABLE()               __HAL_RCC_DMA1_CLK_ENABLE()

#define DACx_CLK_ENABLE()               __HAL_RCC_DAC_CLK_ENABLE()
#define DACx_FORCE_RESET()              __HAL_RCC_DAC_FORCE_RESET()
#define DACx_RELEASE_RESET()            __HAL_RCC_DAC_RELEASE_RESET()

/* Definition for DACx Channel Pin */
#define DACx_CHANNEL_PIN                GPIO_PIN_4
#define DACx_CHANNEL_GPIO_PORT          GPIOA

/* Definition for DACx's Channel */
#define DACx_DMA_CHANNEL                DMA_CHANNEL_7

#define DACx_CHANNEL                    DAC_CHANNEL_1

/* Definition for DACx's DMA_STREAM */
#define DACx_DMA_INSTANCE               DMA1_Stream5

/* Definition for DACx's NVIC */
#define DACx_DMA_IRQn                   DMA1_Stream5_IRQn
#define DACx_DMA_IRQHandler             DMA1_Stream5_IRQHandler

/* Definition for DACy clock resources */
#define DACy                            DAC
#define DACy_CHANNEL_GPIO_CLK_ENABLE()  __HAL_RCC_GPIOA_CLK_ENABLE()
#define DMAy_CLK_ENABLE()               __HAL_RCC_DMA1_CLK_ENABLE()

#define DACy_CLK_ENABLE()               __HAL_RCC_DAC_CLK_ENABLE()
#define DACy_FORCE_RESET()              __HAL_RCC_DAC_FORCE_RESET()
#define DACy_RELEASE_RESET()            __HAL_RCC_DAC_RELEASE_RESET()

/* Definition for DACy Channel Pin */
#define DACy_CHANNEL_PIN                GPIO_PIN_5
#define DACy_CHANNEL_GPIO_PORT          GPIOA

/* Definition for DACy's Channel */
#define DACy_DMA_CHANNEL                DMA_CHANNEL_7

#define DACy_CHANNEL                    DAC_CHANNEL_2

/* Definition for DACy's DMA_STREAM */
#define DACy_DMA_INSTANCE               DMA1_Stream6

/* Definition for DACy's NVIC */
#define DACy_DMA_IRQn                   DMA1_Stream6_IRQn
#define DACy_DMA_IRQHandler             DMA1_Stream6_IRQHandler

/* Definition for TIMx clock resources */
#define TIMx                           TIM9
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM9_CLK_ENABLE()


/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM1_BRK_TIM9_IRQn
#define TIMx_IRQHandler                TIM1_BRK_TIM9_IRQHandler

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* IRQ Handler treatment functions */
void USARTx_CharReception_Callback(void);
void USARTy_CharReception_Callback(void);
void Error_Callback(void);

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
