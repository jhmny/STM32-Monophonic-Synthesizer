/*
 * Codec.cpp
 *
 *  Created on: Sep 12, 2021
 *      Author: Joshua
 */

#include "Codec.h"

//#include "stm32f7xx_hal_conf.h"
#include "stm32f7xx_hal.h"

#include "stm32f7xx.h"
#include "stm32f7xx_it.h"

extern I2C_HandleTypeDef hi2c1;

#define CODEC_RESET_Pin GPIO_PIN_4
//FOR HAL FUNCTIONS
//#include "stm32F7xx_hal.h"

Codec::Codec() {
	// TODO Auto-generated constructor stub

}

Codec::~Codec() {
	// TODO Auto-generated destructor stub
}

uint8_t Codec::init(){
	uint8_t status = 0;
	HAL_GPIO_WritePin(GPIOD,CODEC_RESET_Pin, GPIO_PIN_SET);
	status += write(0x04, 0xaf);
	status += write(0x06, 0x07);
	status += write(0x02, 0x9e);

	return status;
}

uint8_t Codec::write(uint8_t reg, uint8_t val){
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write(&hi2c1, 0x94, reg, 1, &val, sizeof(val), HAL_MAX_DELAY);
	if (status != HAL_OK){
		return 1;
	}
	return 0;
}

