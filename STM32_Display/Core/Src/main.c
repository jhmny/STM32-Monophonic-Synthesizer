/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdio.h>
#include "ssd1306.h"
#include "fonts.h"
#include "test.h"
#include "bitmap.h"
#include "sine_animation.h"

#include "llist.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  /* USER CODE BEGIN 2 */

   	  	  	SSD1306_Init (); // initialize the LCD screen display

 //print something on the screen
   	  	  	SSD1306_GotoXY (10,10); 					// goto 10, 10
   	  	  	SSD1306_Puts ("ECE 186B", &Font_11x18, 1); // print ECE 186B & our names
   	  	  	SSD1306_GotoXY (10, 30);
   	  	  	SSD1306_Puts ("Joshua Mendoza", &Font_7x10, 1);
   	  	  	SSD1306_GotoXY (10, 40);
   	  	  	SSD1306_Puts ("Megan Abundo", &Font_7x10, 1);
   	  	  	SSD1306_GotoXY (10, 50);
   	  	  	SSD1306_Puts ("Paris Villarrial", &Font_7x10, 1);
   	  	  	SSD1306_UpdateScreen(); 					// update screen [DISPLAY]

   	  	  	HAL_Delay (1000);							//2 second delay

//   	  	  	SSD1306_Stopscroll(); 						//Stop Scrolling, it will go on forever otherwise
//  	  	  	SSD1306_Clear();


///////Upload Custom Image by using a drawn bitmap//////////////
//   	  	  	SSD1306_DrawBitmap(30,0,FSULogo,128,64,1); //custom bitmap for a custom image
// 	  	  	  	SSD1306_Clear();
//    	  	  	SSD1306_DrawBitmap(0,0,wave1,128,64,1);
//    	  	  	SSD1306_InvertDisplay(1);
//    	  	  	SSD1306_UpdateScreen();

//   	  	  	HAL_Delay (2000);							//2 second delay

 // 	  	  	SSD1306_ScrollLeft(0x00, 0x0f); 			//Scroll entire screen left
 // 	  	  	HAL_Delay (2000); 							//2 second delay

//  	  	  	SSD1306_ScrollRight(0x00, 0x0f); 			//Scroll entire screen right
//  	  	  	HAL_Delay (2000);							//2 second delay

//   	  	  	SSD1306_Scrolldiagright(0x00, 0x0f); 		//Scroll entire screen diagonally right
//	  	  	HAL_Delay (2000); 							//2 second delay

//   	  	  	SSD1306_Scrolldiagleft(0x00, 0x0f); 		//Scroll entire screen diagonally left
//  	  	  	HAL_Delay (2000);							//2 second delay

  //	  		SSD1306_Stopscroll();						//stop scrolling

///////////////////////////////INVERT FUNCTIONS//////////////////////////////////////////////////////////////
   	  		//SSD1306_InvertDisplay(1); 					//Invert the display
   	  		//HAL_Delay (2000);							//2 second delay
   	  		//SSD1306_InvertDisplay(0); 					//normalize display

////////////////////////////////TESTING FUCNTIONS/////////////////////////////////////////////////////////////////

   	  	  	//TestLines(1);
   	  	  	//HAL_Delay(1000);
   	  	  	//TestTriangles(1);
   	  	  	//HAL_Delay(1000);
   	  	  	//TestRectangles(1);
   	  	  	//HAL_Delay(1000);
   	  	  	//TestFilledRectangles(1);
   	  	  	//HAL_Delay(1000);
   	  	  	//TestCircles(6,1);
   	  	  	//HAL_Delay(1000);
   	  	  	//TestFilledCircles(6,1);
   	  	  	//HAL_Delay(1000);

///////////////////////////////////////////////////////////////////////////////////////////


/*
   		  //////////////////////////////////////////////////CUSTOM ANIMATION//////////////////////////////////////
   		  	  	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave1,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave2,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave3,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave4,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave5,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave6,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave7,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave8,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave9,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave10,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave11,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave12,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave13,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave14,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();

   		     	  	  	SSD1306_Clear();
   		     	  	  	SSD1306_DrawBitmap(0,0,wave15,128,64,1);
   		     	  	  	SSD1306_InvertDisplay(1);
   		     	  	  	SSD1306_UpdateScreen();
//////////////////////////////////////////////////////////////////////////////////
 */



  /* USER CODE END 2 */

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 400000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
