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
#include <float.h>
#include <math.h>
#include <stdio.h>
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

I2S_HandleTypeDef hi2s1;

UART_HandleTypeDef huart4;
DMA_HandleTypeDef hdma_uart4_rx;

/* USER CODE BEGIN PV */
uint8_t paramvalue[32];
uint8_t vhbtn = 0;
int8_t transpose, scale;

uint16_t counter[12], output, output1, output2, pwval, pwmval, modval;

uint16_t lfo1rate, lfo1 = 63, lfo1cnt = 1, lfo1pol = 1;
uint16_t lfo2rate, lfo2 = 63, lfo2cnt = 1, lfo2pol = 1;
uint16_t lfo3rate, lfo3 = 63, lfo3cnt = 1, lfo3pol = 1;
uint16_t lfo4rate, lfo4 = 63, lfo4cnt = 1, lfo4pol = 1;

float vcfkflvl, envkflvl, oscmix, vcfreleaselvl = 0.000001f, vcareleaselvl = 0.000001f, resonance;
float vcfattackrate[6], vcfdecayrate[6], vcfsustainlvl[6], vcfreleaserate[6];
float vcfvellvl[6], vcavellvl[6], vcfenvlvl;
float vcfattack, vcfdecay, vcfsustain, vcfrelease;
float vcaattackrate[6], vcadecayrate[6], vcasustainlvl[6], vcareleaserate[6];
float vcaattack, vcadecay, vcasustain, vcarelease;

void play_note(uint8_t, uint8_t);
void stop_note(uint8_t);
void LocalMidiHandler(uint8_t, uint8_t);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2S1_Init(void);
static void MX_DMA_Init(void);
static void MX_UART4_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const uint16_t triangle_wave[]  = {
0x400,0x800,0xc00,0x1000,0x1400,0x1800,0x1c00,0x2000,
0x2400,0x2800,0x2c00,0x3000,0x3400,0x3800,0x3c00,0x4000,
0x4400,0x4800,0x4c00,0x5000,0x5400,0x5800,0x5c00,0x6000,
0x6400,0x6800,0x6c00,0x7000,0x7400,0x7800,0x7c00,0x8000,
0x83ff,0x87ff,0x8bff,0x8fff,0x93ff,0x97ff,0x9bff,0x9fff,
0xa3ff,0xa7ff,0xabff,0xafff,0xb3ff,0xb7ff,0xbbff,0xbfff,
0xc3ff,0xc7ff,0xcbff,0xcfff,0xd3ff,0xd7ff,0xdbff,0xdfff,
0xe3ff,0xe7ff,0xebff,0xefff,0xf3ff,0xf7ff,0xfbff,0xffff,
0xfbff,0xf7ff,0xf3ff,0xefff,0xebff,0xe7ff,0xe3ff,0xdfff,
0xdbff,0xd7ff,0xd3ff,0xcfff,0xcbff,0xc7ff,0xc3ff,0xbfff,
0xbbff,0xb7ff,0xb3ff,0xafff,0xabff,0xa7ff,0xa3ff,0x9fff,
0x9bff,0x97ff,0x93ff,0x8fff,0x8bff,0x87ff,0x83ff,0x8000,
0x7c00,0x7800,0x7400,0x7000,0x6c00,0x6800,0x6400,0x6000,
0x5c00,0x5800,0x5400,0x5000,0x4c00,0x4800,0x4400,0x4000,
0x3c00,0x3800,0x3400,0x3000,0x2c00,0x2800,0x2400,0x2000,
0x1c00,0x1800,0x1400,0x1000,0xc00,0x800,0x400,0x0,
};

const uint16_t sin_wave[]  = {
		0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9c,0x9f,0xa2,0xa5,0xa8,0xab,0xae,
		0xb0,0xb3,0xb6,0xb9,0xbc,0xbf,0xc1,0xc4,0xc7,0xc9,0xcc,0xce,0xd1,0xd3,0xd5,0xd8,
		0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xed,0xef,0xf0,0xf2,0xf3,0xf5,
		0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfc,0xfd,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,
		0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfd,0xfc,0xfc,0xfb,0xfa,0xf9,0xf8,0xf7,
		0xf6,0xf5,0xf3,0xf2,0xf0,0xef,0xed,0xec,0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,
		0xda,0xd8,0xd5,0xd3,0xd1,0xce,0xcc,0xc9,0xc7,0xc4,0xc1,0xbf,0xbc,0xb9,0xb6,0xb3,
		0xb0,0xae,0xab,0xa8,0xa5,0xa2,0x9f,0x9c,0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,
		0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,0x67,0x63,0x60,0x5d,0x5a,0x57,0x54,0x51,
		0x4f,0x4c,0x49,0x46,0x43,0x40,0x3e,0x3b,0x38,0x36,0x33,0x31,0x2e,0x2c,0x2a,0x27,
		0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x15,0x13,0x12,0x10,0x0f,0x0d,0x0c,0x0a,
		0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x03,0x02,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x05,0x06,0x07,0x08,
		0x09,0x0a,0x0c,0x0d,0x0f,0x10,0x12,0x13,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
		0x25,0x27,0x2a,0x2c,0x2e,0x31,0x33,0x36,0x38,0x3b,0x3e,0x40,0x43,0x46,0x49,0x4c,
		0x4f,0x51,0x54,0x57,0x5a,0x5d,0x60,0x63,0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c
};

const uint16_t sin_wave2[]  = {
		0x8324, 0x8647, 0x896A, 0x8C8B, 0x8FAB, 0x92C7, 0x95E1, 0x98F8,
		        0x9C0B, 0x9F19, 0xA223, 0xA527, 0xA826, 0xAB1F, 0xAE10, 0xB0FB,
		        0xB3DE, 0xB6B9, 0xB98C, 0xBC56, 0xBF17, 0xC1CD, 0xC47A, 0xC71C,
		        0xC9B3, 0xCC3F, 0xCEBF, 0xD133, 0xD39A, 0xD5F5, 0xD842, 0xDA82,
		        0xDCB3, 0xDED7, 0xE0EB, 0xE2F1, 0xE4E8, 0xE6CF, 0xE8A6, 0xEA6D,
		        0xEC23, 0xEDC9, 0xEF5E, 0xF0E2, 0xF254, 0xF3B5, 0xF504, 0xF641,
		        0xF76B, 0xF884, 0xF989, 0xFA7C, 0xFB5C, 0xFC29, 0xFCE3, 0xFD89,
		        0xFE1D, 0xFE9C, 0xFF09, 0xFF61, 0xFFA6, 0xFFD8, 0xFFF5, 0xFFFF,
		        0xFFF5, 0xFFD8, 0xFFA6, 0xFF61, 0xFF09, 0xFE9C, 0xFE1D, 0xFD89,
		        0xFCE3, 0xFC29, 0xFB5C, 0xFA7C, 0xF989, 0xF884, 0xF76B, 0xF641,
		        0xF504, 0xF3B5, 0xF254, 0xF0E2, 0xEF5E, 0xEDC9, 0xEC23, 0xEA6D,
		        0xE8A6, 0xE6CF, 0xE4E8, 0xE2F1, 0xE0EB, 0xDED7, 0xDCB3, 0xDA82,
		        0xD842, 0xD5F5, 0xD39A, 0xD133, 0xCEBF, 0xCC3F, 0xC9B3, 0xC71C,
		        0xC47A, 0xC1CD, 0xBF17, 0xBC56, 0xB98C, 0xB6B9, 0xB3DE, 0xB0FB,
		        0xAE10, 0xAB1F, 0xA826, 0xA527, 0xA223, 0x9F19, 0x9C0B, 0x98F8,
		        0x95E1, 0x92C7, 0x8FAB, 0x8C8B, 0x896A, 0x8647, 0x8324, 0x8000,
		        0x7CDB, 0x79B8, 0x7695, 0x7374, 0x7054, 0x6D38, 0x6A1E, 0x6707,
		        0x63F4, 0x60E6, 0x5DDC, 0x5AD8, 0x57D9, 0x54E0, 0x51EF, 0x4F04,
		        0x4C21, 0x4946, 0x4673, 0x43A9, 0x40E8, 0x3E32, 0x3B85, 0x38E3,
		        0x364C, 0x33C0, 0x3140, 0x2ECC, 0x2C65, 0x2A0A, 0x27BD, 0x257D,
		        0x234C, 0x2128, 0x1F14, 0x1D0E, 0x1B17, 0x1930, 0x1759, 0x1592,
		        0x13DC, 0x1236, 0x10A1, 0x0F1D, 0x0DAB, 0x0C4A, 0x0AFB, 0x09BE,
		        0x0894, 0x077B, 0x0676, 0x0583, 0x04A3, 0x03D6, 0x031C, 0x0276,
		        0x01E2, 0x0163, 0x00F6, 0x009E, 0x0059, 0x0027, 0x000A, 0x0000,
		        0x000A, 0x0027, 0x0059, 0x009E, 0x00F6, 0x0163, 0x01E2, 0x0276,
		        0x031C, 0x03D6, 0x04A3, 0x0583, 0x0676, 0x077B, 0x0894, 0x09BE,
		        0x0AFB, 0x0C4A, 0x0DAB, 0x0F1D, 0x10A1, 0x1236, 0x13DC, 0x1592,
		        0x1759, 0x1930, 0x1B17, 0x1D0E, 0x1F14, 0x2128, 0x234C, 0x257D,
		        0x27BD, 0x2A0A, 0x2C65, 0x2ECC, 0x3140, 0x33C0, 0x364C, 0x38E3,
		        0x3B85, 0x3E32, 0x40E8, 0x43A9, 0x4673, 0x4946, 0x4C21, 0x4F04,
		        0x51EF, 0x54E0, 0x57D9, 0x5AD8, 0x5DDC, 0x60E6, 0x63F4, 0x6707,
		        0x6A1E, 0x6D38, 0x7054, 0x7374, 0x7695, 0x79B8, 0x7CDB, 0x7FFF
};

const float_t triangle[] = {

	0.00000f, 0.00387f, 0.00774f, 0.01161f, 0.01550f, 0.01939f, 0.02329f, 0.02720f,
	0.03113f, 0.03507f, 0.03902f, 0.04299f, 0.04698f, 0.05098f, 0.05500f, 0.05903f,
	0.06307f, 0.06712f, 0.07119f, 0.07526f, 0.07933f, 0.08341f, 0.08749f, 0.09157f,
	0.09564f, 0.09971f, 0.10377f, 0.10782f, 0.11186f, 0.11588f, 0.11990f, 0.12389f,
	0.12787f, 0.13184f, 0.13578f, 0.13972f, 0.14364f, 0.14754f, 0.15144f, 0.15532f,
	0.15920f, 0.16307f, 0.16694f, 0.17080f, 0.17467f, 0.17853f, 0.18241f, 0.18629f,
	0.19018f, 0.19408f, 0.19800f, 0.20193f, 0.20587f, 0.20983f, 0.21381f, 0.21781f,
	0.22182f, 0.22584f, 0.22988f, 0.23393f, 0.23800f, 0.24207f, 0.24615f, 0.25023f,
	0.25432f, 0.25840f, 0.26249f, 0.26657f, 0.27064f, 0.27470f, 0.27875f, 0.28279f,
	0.28682f, 0.29082f, 0.29481f, 0.29879f, 0.30274f, 0.30668f, 0.31061f, 0.31452f,
	0.31841f, 0.32229f, 0.32616f, 0.33002f, 0.33388f, 0.33773f, 0.34158f, 0.34544f,
	0.34930f, 0.35316f, 0.35704f, 0.36092f, 0.36482f, 0.36874f, 0.37267f, 0.37662f,
	0.38059f, 0.38457f, 0.38858f, 0.39260f, 0.39664f, 0.40069f, 0.40476f, 0.40884f,
	0.41294f, 0.41704f, 0.42114f, 0.42524f, 0.42935f, 0.43345f, 0.43754f, 0.44163f,
	0.44570f, 0.44976f, 0.45380f, 0.45783f, 0.46183f, 0.46582f, 0.46978f, 0.47373f,
	0.47765f, 0.48156f, 0.48544f, 0.48931f, 0.49317f, 0.49701f, 0.50085f, 0.50468f,
	0.50850f, 0.51233f, 0.51616f, 0.51999f, 0.52384f, 0.52769f, 0.53157f, 0.53546f,
	0.53937f, 0.54330f, 0.54725f, 0.55123f, 0.55523f, 0.55925f, 0.56330f, 0.56736f,
	0.57145f, 0.57556f, 0.57967f, 0.58380f, 0.58794f, 0.59209f, 0.59623f, 0.60037f,
	0.60451f, 0.60864f, 0.61275f, 0.61685f, 0.62092f, 0.62498f, 0.62901f, 0.63301f,
	0.63698f, 0.64093f, 0.64485f, 0.64874f, 0.65261f, 0.65645f, 0.66028f, 0.66408f,
	0.66786f, 0.67164f, 0.67541f, 0.67917f, 0.68294f, 0.68671f, 0.69050f, 0.69430f,
	0.69811f, 0.70195f, 0.70582f, 0.70972f, 0.71365f, 0.71761f, 0.72161f, 0.72565f,
	0.72971f, 0.73382f, 0.73795f, 0.74211f, 0.74630f, 0.75051f, 0.75473f, 0.75897f,
	0.76321f, 0.76745f, 0.77169f, 0.77591f, 0.78012f, 0.78430f, 0.78845f, 0.79257f,
	0.79665f, 0.80069f, 0.80468f, 0.80862f, 0.81252f, 0.81637f, 0.82017f, 0.82392f,
	0.82764f, 0.83131f, 0.83495f, 0.83857f, 0.84217f, 0.84575f, 0.84934f, 0.85292f,
	0.85653f, 0.86016f, 0.86382f, 0.86752f, 0.87128f, 0.87510f, 0.87898f, 0.88293f,
	0.88696f, 0.89106f, 0.89525f, 0.89952f, 0.90387f, 0.90830f, 0.91279f, 0.91734f,
	0.92195f, 0.92660f, 0.93128f, 0.93596f, 0.94064f, 0.94530f, 0.94991f, 0.95445f,
	0.95890f, 0.96325f, 0.96745f, 0.97150f, 0.97536f, 0.97902f, 0.98245f, 0.98562f,
	0.98853f, 0.99114f, 0.99344f, 0.99541f, 0.99705f, 0.99833f, 0.99926f, 0.99981f,
	1.00000f, 0.99981f, 0.99926f, 0.99833f, 0.99705f, 0.99541f, 0.99344f, 0.99114f,
	0.98853f, 0.98562f, 0.98245f, 0.97902f, 0.97536f, 0.97150f, 0.96745f, 0.96325f,
	0.95890f, 0.95445f, 0.94991f, 0.94530f, 0.94064f, 0.93596f, 0.93128f, 0.92660f,
	0.92195f, 0.91734f, 0.91279f, 0.90830f, 0.90387f, 0.89952f, 0.89525f, 0.89106f,
	0.88696f, 0.88293f, 0.87898f, 0.87510f, 0.87128f, 0.86752f, 0.86382f, 0.86016f,
	0.85653f, 0.85292f, 0.84934f, 0.84575f, 0.84217f, 0.83857f, 0.83495f, 0.83131f,
	0.82764f, 0.82392f, 0.82017f, 0.81637f, 0.81252f, 0.80862f, 0.80468f, 0.80069f,
	0.79665f, 0.79257f, 0.78845f, 0.78430f, 0.78012f, 0.77591f, 0.77169f, 0.76745f,
	0.76321f, 0.75897f, 0.75473f, 0.75051f, 0.74630f, 0.74211f, 0.73795f, 0.73382f,
	0.72971f, 0.72565f, 0.72161f, 0.71761f, 0.71365f, 0.70972f, 0.70582f, 0.70195f,
	0.69811f, 0.69430f, 0.69050f, 0.68671f, 0.68294f, 0.67917f, 0.67541f, 0.67164f,
	0.66786f, 0.66408f, 0.66028f, 0.65645f, 0.65261f, 0.64874f, 0.64485f, 0.64093f,
	0.63698f, 0.63301f, 0.62901f, 0.62498f, 0.62092f, 0.61685f, 0.61275f, 0.60864f,
	0.60451f, 0.60037f, 0.59623f, 0.59209f, 0.58794f, 0.58380f, 0.57967f, 0.57556f,
	0.57145f, 0.56736f, 0.56330f, 0.55925f, 0.55523f, 0.55123f, 0.54725f, 0.54330f,
	0.53937f, 0.53546f, 0.53157f, 0.52769f, 0.52384f, 0.51999f, 0.51616f, 0.51233f,
	0.50850f, 0.50468f, 0.50085f, 0.49701f, 0.49317f, 0.48931f, 0.48544f, 0.48156f,
	0.47765f, 0.47373f, 0.46978f, 0.46582f, 0.46183f, 0.45783f, 0.45380f, 0.44976f,
	0.44570f, 0.44163f, 0.43754f, 0.43345f, 0.42935f, 0.42524f, 0.42114f, 0.41704f,
	0.41294f, 0.40884f, 0.40476f, 0.40069f, 0.39664f, 0.39260f, 0.38858f, 0.38457f,
	0.38059f, 0.37662f, 0.37267f, 0.36874f, 0.36482f, 0.36092f, 0.35704f, 0.35316f,
	0.34930f, 0.34544f, 0.34158f, 0.33773f, 0.33388f, 0.33002f, 0.32616f, 0.32229f,
	0.31841f, 0.31452f, 0.31061f, 0.30668f, 0.30274f, 0.29879f, 0.29481f, 0.29082f,
	0.28682f, 0.28279f, 0.27875f, 0.27470f, 0.27064f, 0.26657f, 0.26249f, 0.25840f,
	0.25432f, 0.25023f, 0.24615f, 0.24207f, 0.23800f, 0.23393f, 0.22988f, 0.22584f,
	0.22182f, 0.21781f, 0.21381f, 0.20983f, 0.20587f, 0.20193f, 0.19800f, 0.19408f,
	0.19018f, 0.18629f, 0.18241f, 0.17853f, 0.17467f, 0.17080f, 0.16694f, 0.16307f,
	0.15920f, 0.15532f, 0.15144f, 0.14754f, 0.14364f, 0.13972f, 0.13578f, 0.13184f,
	0.12787f, 0.12389f, 0.11990f, 0.11588f, 0.11186f, 0.10782f, 0.10377f, 0.09971f,
	0.09564f, 0.09157f, 0.08749f, 0.08341f, 0.07933f, 0.07526f, 0.07119f, 0.06712f,
	0.06307f, 0.05903f, 0.05500f, 0.05098f, 0.04698f, 0.04299f, 0.03902f, 0.03507f,
	0.03113f, 0.02720f, 0.02329f, 0.01939f, 0.01550f, 0.01161f, 0.00774f, 0.00387f,
	-0.00000f, -0.00387f, -0.00774f, -0.01161f, -0.01550f, -0.01939f, -0.02329f, -0.02720f,
	-0.03113f, -0.03507f, -0.03902f, -0.04299f, -0.04698f, -0.05098f, -0.05500f, -0.05903f,
	-0.06307f, -0.06712f, -0.07119f, -0.07526f, -0.07933f, -0.08341f, -0.08749f, -0.09157f,
	-0.09564f, -0.09971f, -0.10377f, -0.10782f, -0.11186f, -0.11588f, -0.11990f, -0.12389f,
	-0.12787f, -0.13184f, -0.13578f, -0.13972f, -0.14364f, -0.14754f, -0.15144f, -0.15532f,
	-0.15920f, -0.16307f, -0.16694f, -0.17080f, -0.17467f, -0.17853f, -0.18241f, -0.18629f,
	-0.19018f, -0.19408f, -0.19800f, -0.20193f, -0.20587f, -0.20983f, -0.21381f, -0.21781f,
	-0.22182f, -0.22584f, -0.22988f, -0.23393f, -0.23800f, -0.24207f, -0.24615f, -0.25023f,
	-0.25432f, -0.25840f, -0.26249f, -0.26657f, -0.27064f, -0.27470f, -0.27875f, -0.28279f,
	-0.28682f, -0.29082f, -0.29481f, -0.29879f, -0.30274f, -0.30668f, -0.31061f, -0.31452f,
	-0.31841f, -0.32229f, -0.32616f, -0.33002f, -0.33388f, -0.33773f, -0.34158f, -0.34544f,
	-0.34930f, -0.35316f, -0.35704f, -0.36092f, -0.36482f, -0.36874f, -0.37267f, -0.37662f,
	-0.38059f, -0.38457f, -0.38858f, -0.39260f, -0.39664f, -0.40069f, -0.40476f, -0.40884f,
	-0.41294f, -0.41704f, -0.42114f, -0.42524f, -0.42935f, -0.43345f, -0.43754f, -0.44163f,
	-0.44570f, -0.44976f, -0.45380f, -0.45783f, -0.46183f, -0.46582f, -0.46978f, -0.47373f,
	-0.47765f, -0.48156f, -0.48544f, -0.48931f, -0.49317f, -0.49701f, -0.50085f, -0.50468f,
	-0.50850f, -0.51233f, -0.51616f, -0.51999f, -0.52384f, -0.52769f, -0.53157f, -0.53546f,
	-0.53937f, -0.54330f, -0.54725f, -0.55123f, -0.55523f, -0.55925f, -0.56330f, -0.56736f,
	-0.57145f, -0.57556f, -0.57967f, -0.58380f, -0.58794f, -0.59209f, -0.59623f, -0.60037f,
	-0.60451f, -0.60864f, -0.61275f, -0.61685f, -0.62092f, -0.62498f, -0.62901f, -0.63301f,
	-0.63698f, -0.64093f, -0.64485f, -0.64874f, -0.65261f, -0.65645f, -0.66028f, -0.66408f,
	-0.66786f, -0.67164f, -0.67541f, -0.67917f, -0.68294f, -0.68671f, -0.69050f, -0.69430f,
	-0.69811f, -0.70195f, -0.70582f, -0.70972f, -0.71365f, -0.71761f, -0.72161f, -0.72565f,
	-0.72971f, -0.73382f, -0.73795f, -0.74211f, -0.74630f, -0.75051f, -0.75473f, -0.75897f,
	-0.76321f, -0.76745f, -0.77169f, -0.77591f, -0.78012f, -0.78430f, -0.78845f, -0.79257f,
	-0.79665f, -0.80069f, -0.80468f, -0.80862f, -0.81252f, -0.81637f, -0.82017f, -0.82392f,
	-0.82764f, -0.83131f, -0.83495f, -0.83857f, -0.84217f, -0.84575f, -0.84934f, -0.85292f,
	-0.85653f, -0.86016f, -0.86382f, -0.86752f, -0.87128f, -0.87510f, -0.87898f, -0.88293f,
	-0.88696f, -0.89106f, -0.89525f, -0.89952f, -0.90387f, -0.90830f, -0.91279f, -0.91734f,
	-0.92195f, -0.92660f, -0.93128f, -0.93596f, -0.94064f, -0.94530f, -0.94991f, -0.95445f,
	-0.95890f, -0.96325f, -0.96745f, -0.97150f, -0.97536f, -0.97902f, -0.98245f, -0.98562f,
	-0.98853f, -0.99114f, -0.99344f, -0.99541f, -0.99705f, -0.99833f, -0.99926f, -0.99981f,
	-1.00000f, -0.99981f, -0.99926f, -0.99833f, -0.99705f, -0.99541f, -0.99344f, -0.99114f,
	-0.98853f, -0.98562f, -0.98245f, -0.97902f, -0.97536f, -0.97150f, -0.96745f, -0.96325f,
	-0.95890f, -0.95445f, -0.94991f, -0.94530f, -0.94064f, -0.93596f, -0.93128f, -0.92660f,
	-0.92195f, -0.91734f, -0.91279f, -0.90830f, -0.90387f, -0.89952f, -0.89525f, -0.89106f,
	-0.88696f, -0.88293f, -0.87898f, -0.87510f, -0.87128f, -0.86752f, -0.86382f, -0.86016f,
	-0.85653f, -0.85292f, -0.84934f, -0.84575f, -0.84217f, -0.83857f, -0.83495f, -0.83131f,
	-0.82764f, -0.82392f, -0.82017f, -0.81637f, -0.81252f, -0.80862f, -0.80468f, -0.80069f,
	-0.79665f, -0.79257f, -0.78845f, -0.78430f, -0.78012f, -0.77591f, -0.77169f, -0.76745f,
	-0.76321f, -0.75897f, -0.75473f, -0.75051f, -0.74630f, -0.74211f, -0.73795f, -0.73382f,
	-0.72971f, -0.72565f, -0.72161f, -0.71761f, -0.71365f, -0.70972f, -0.70582f, -0.70195f,
	-0.69811f, -0.69430f, -0.69050f, -0.68671f, -0.68294f, -0.67917f, -0.67541f, -0.67164f,
	-0.66786f, -0.66408f, -0.66028f, -0.65645f, -0.65261f, -0.64874f, -0.64485f, -0.64093f,
	-0.63698f, -0.63301f, -0.62901f, -0.62498f, -0.62092f, -0.61685f, -0.61275f, -0.60864f,
	-0.60451f, -0.60037f, -0.59623f, -0.59209f, -0.58794f, -0.58380f, -0.57967f, -0.57556f,
	-0.57145f, -0.56736f, -0.56330f, -0.55925f, -0.55523f, -0.55123f, -0.54725f, -0.54330f,
	-0.53937f, -0.53546f, -0.53157f, -0.52769f, -0.52384f, -0.51999f, -0.51616f, -0.51233f,
	-0.50850f, -0.50468f, -0.50085f, -0.49701f, -0.49317f, -0.48931f, -0.48544f, -0.48156f,
	-0.47765f, -0.47373f, -0.46978f, -0.46582f, -0.46183f, -0.45783f, -0.45380f, -0.44976f,
	-0.44570f, -0.44163f, -0.43754f, -0.43345f, -0.42935f, -0.42524f, -0.42114f, -0.41704f,
	-0.41294f, -0.40884f, -0.40476f, -0.40069f, -0.39664f, -0.39260f, -0.38858f, -0.38457f,
	-0.38059f, -0.37662f, -0.37267f, -0.36874f, -0.36482f, -0.36092f, -0.35704f, -0.35316f,
	-0.34930f, -0.34544f, -0.34158f, -0.33773f, -0.33388f, -0.33002f, -0.32616f, -0.32229f,
	-0.31841f, -0.31452f, -0.31061f, -0.30668f, -0.30274f, -0.29879f, -0.29481f, -0.29082f,
	-0.28682f, -0.28279f, -0.27875f, -0.27470f, -0.27064f, -0.26657f, -0.26249f, -0.25840f,
	-0.25432f, -0.25023f, -0.24615f, -0.24207f, -0.23800f, -0.23393f, -0.22988f, -0.22584f,
	-0.22182f, -0.21781f, -0.21381f, -0.20983f, -0.20587f, -0.20193f, -0.19800f, -0.19408f,
	-0.19018f, -0.18629f, -0.18241f, -0.17853f, -0.17467f, -0.17080f, -0.16694f, -0.16307f,
	-0.15920f, -0.15532f, -0.15144f, -0.14754f, -0.14364f, -0.13972f, -0.13578f, -0.13184f,
	-0.12787f, -0.12389f, -0.11990f, -0.11588f, -0.11186f, -0.10782f, -0.10377f, -0.09971f,
	-0.09564f, -0.09157f, -0.08749f, -0.08341f, -0.07933f, -0.07526f, -0.07119f, -0.06712f,
	-0.06307f, -0.05903f, -0.05500f, -0.05098f, -0.04698f, -0.04299f, -0.03902f, -0.03507f,
	-0.03113f, -0.02720f, -0.02329f, -0.01939f, -0.01550f, -0.01161f, -0.00774f, -0.00387f};

uint8_t UART4_rxBuffer[8] = {0};
uint8_t msgnum, midimsg, received_char, key, velocity, ctrl, data;
uint8_t wavesel, velsel, pwm, pwm2, mod, vcf, tun, det, sus, notepos, bend, param, patch;



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
  MX_I2S1_Init();
  MX_DMA_Init();
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */
  //HAL_I2S_Transmit_DMA(&hi2s1, sendBuff, 8);
  HAL_UART_Receive_DMA(&huart4, UART4_rxBuffer, 8);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1){
	  //HAL_I2S_Transmit(&hi2s1, triangle_wave, sizeof(triangle_wave)/sizeof(triangle_wave[0]), 10);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Macro to configure the PLL multiplication factor
  */
  __HAL_RCC_PLL_PLLM_CONFIG(16);
  /** Macro to configure the PLL clock source
  */
  __HAL_RCC_PLL_PLLSOURCE_CONFIG(RCC_PLLSOURCE_HSI);
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
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
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
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_UART4|RCC_PERIPHCLK_I2S;
  PeriphClkInitStruct.PLLI2S.PLLI2SN = 192;
  PeriphClkInitStruct.PLLI2S.PLLI2SP = RCC_PLLP_DIV2;
  PeriphClkInitStruct.PLLI2S.PLLI2SR = 2;
  PeriphClkInitStruct.PLLI2S.PLLI2SQ = 2;
  PeriphClkInitStruct.PLLI2SDivQ = 1;
  PeriphClkInitStruct.I2sClockSelection = RCC_I2SCLKSOURCE_PLLI2S;
  PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2S1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2S1_Init(void)
{

  /* USER CODE BEGIN I2S1_Init 0 */

  /* USER CODE END I2S1_Init 0 */

  /* USER CODE BEGIN I2S1_Init 1 */

  /* USER CODE END I2S1_Init 1 */
  hi2s1.Instance = SPI1;
  hi2s1.Init.Mode = I2S_MODE_MASTER_TX;
  hi2s1.Init.Standard = I2S_STANDARD_PHILIPS;
  hi2s1.Init.DataFormat = I2S_DATAFORMAT_16B;
  hi2s1.Init.MCLKOutput = I2S_MCLKOUTPUT_DISABLE;
  hi2s1.Init.AudioFreq = I2S_AUDIOFREQ_8K;
  hi2s1.Init.CPOL = I2S_CPOL_LOW;
  hi2s1.Init.ClockSource = I2S_CLOCK_PLL;
  if (HAL_I2S_Init(&hi2s1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2S1_Init 2 */

  /* USER CODE END I2S1_Init 2 */

}

/**
  * @brief UART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_UART4_Init(void)
{

  /* USER CODE BEGIN UART4_Init 0 */

  /* USER CODE END UART4_Init 0 */

  /* USER CODE BEGIN UART4_Init 1 */

  /* USER CODE END UART4_Init 1 */
  huart4.Instance = UART4;
  huart4.Init.BaudRate = 31250;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN UART4_Init 2 */

  /* USER CODE END UART4_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_I2SEx_TxRxHalfCpltCallback(I2S_HandleTypeDef * hi2s1){

}

//buffer is full here, do something when full
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    HAL_UART_Transmit(&huart4, UART4_rxBuffer, 8, 1000);
    HAL_UART_Receive_DMA(&huart4, UART4_rxBuffer, 8);

    __IO uint32_t received_char;

    received_char = UART4_rxBuffer[msgnum];

    if(received_char == 0xF & msgnum)
      {
    	  vhbtn = 1;
    	  return;
      }

    if(!vhbtn)
      {
    	  if((received_char == 0xF7)  & msgnum == 0)
    	  {
    		  return;
    	  }


    	  //no note message
    	  if(received_char < 0x80 & msgnum == 0)
    		  return;

    	  if(msgnum == 0)
    	  {
    		  midimsg = received_char;
    	  }
    	  if(msgnum == 1)
    	  {
    		  key = received_char;
    		  ctrl = received_char;
    	  }
    	  if(msgnum == 2)
    	  {

    		  velocity = received_char;
    		  data = received_char;
    	  }

    	  msgnum++;

    	  if(msgnum == 3)
    	  {
    		  msgnum = 0;
    		  ProcessReceivedMidiDatas();
    	  }
      }

    if(vhbtn)
        {
      	  if((received_char == 0xF7)  & msgnum == 0)
      	  {
      		  return;
      	  }

      	  if(received_char < 0x80 & msgnum == 0)return;

      	  if(msgnum == 0)
      	  {
      		  midimsg = received_char;
      	  }
      	  if(msgnum == 1)
      	  {
      		  key = received_char;
      		  ctrl = received_char;
      	  }
      	  if(msgnum == 2)
      	  {
      		  velocity = received_char;
      		  data = received_char;
      	  }

      	  msgnum++;

      	  if(msgnum == 3)
      	  {
      		  msgnum = 0;
      		  param = key - 0x24;
      		  vhbtn = 0;
      	  }
        }

}

void ProcessReceivedMidiDatas(void)
{
			uint8_t chan = midimsg & 0xf;
			uint8_t msgtype = midimsg & 0xf0;
			//HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
			// Not a drum machine, so ignore channel ten
			if(chan == 9)return;

			// Handle MIDI messages
			switch(msgtype)
			{
				case (0x80): // Note Off
					notepos = key + transpose;
					stop_note(notepos);
					break;
				case (0x90): // Note On
					notepos = key + transpose;
					if(!velocity)
					{
						stop_note(notepos);
					}
					else
					{

						play_note(notepos, velocity);
					}
					break;
				case (0xA0): // Poly Aftertouch
					break;
				case (0xB0): // Control Change
        			break;
				case (0xC0): // Program Change
					break;
				case (0xD0): // Mono Aftertouch
					break;
				case (0xE0): // Pitch Bend
					LocalMidiHandler(param, data);
					break;
				case (0xF0): // Parameter Change
					break;
	}
}

// TO DO: RARELY GETS TO 0X90 MESSAGE, CHECK HOW WE EMPTY THE BUFFER
void play_note(uint8_t note, uint8_t velocity){
	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	HAL_I2S_Transmit(&hi2s1, triangle_wave, sizeof(triangle_wave)/sizeof(triangle_wave[0]), 10);
}

void stop_note(uint8_t note){

}

void LocalMidiHandler(uint8_t m_param, uint8_t m_data)
{
	switch(m_param)
	{
		case (0):  // Pitch Wheel
			bend = m_data;
			break;
		case (1): // Modulation Wheel
			if(m_data >= 64)
			{
				mod = (m_data - 64) >> 1;
			}
			break;
		case (2): // Tuning
			tun = m_data;
			break;
		case (3): // Wave Select
			wavesel = m_data >> 5;
			break;
		case (4): // OSC Mix
			oscmix = (((float)(m_data)) * 0.007874f);
			break;
		case (5): // De-Tune
			det = m_data >> 4;
			break;
		case (6): // Scale
			scale = (m_data - 64) >> 2;
			break;
		case (7): // Resonance
			resonance = (((float)(m_data)) * 0.007874f * 4.0f);
			break;
		case (8): // Pulse Width Value
			pwval = m_data;
			break;
		case (9): // VCF Attack
			vcfattack = (((float)(m_data)) * 10.0f);
			break;
		case (10): // VCF Decay
			vcfdecay = (((float)(m_data)) * 10.0f);
			break;
		case (11): // VCF Sustain
			vcfsustain = (((float)(m_data)) * 0.007874f);
			break;
		case (12): // VCF Release
			vcfrelease = (((float)(m_data)) * 10.0f);
			break;
		case (13): // VCA Attack
			vcaattack = (((float)(m_data)) * 10.0f);
			break;
		case (14): // VCA Decay
			vcadecay = (((float)(m_data)) * 10.0f);
			break;
		case (15): // VCA Sustain
			vcasustain = (((float)(m_data)) * 0.007874f);
			break;
		case (16): // VCA Release
			vcarelease = (((float)(m_data)) * 10.0f);
			break;
		case (17): // VCF Follow Level
			vcfkflvl = (((float)(m_data)) * 0.007874f);
			break;
		case (18): // ENV Follow Level
			envkflvl = (((float)(m_data)) * 0.007874f);
			break;
		case (19): // Velocity Select
			velsel = m_data >> 5;
			break;
		case (20): // VCF Envelope Level
			vcfenvlvl = (((float)(m_data)) * 0.007874f);
			break;
		case (21): // Mod LFO rate
			lfo1rate = (128 - m_data) << 2;
			break;
		case (22): // Pwm LFO rate
			lfo2rate = (128 - m_data) << 2;
			break;
		case (23): // Pwm2 LFO rate
			lfo4rate = (128 - m_data) << 2;
			break;
		case (24): // Vcf LFO rate
			lfo3rate = (128 - m_data) << 2;
			break;
		case (25): // VCF LFO Mod level
			vcf = m_data;
			break;
		case (26): // PWM Level
			pwm = m_data;
			break;
		case (27): // PWM2 Level
			pwm2 = m_data;
			break;
		case (28): // Un-assigned
			break;
		case (29): // Un-assigned
			break;
		case (30): // Un-assigned
			break;
		case (31): // Un-assigned
			break;
	}
	paramvalue[m_param] = m_data;
}

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
