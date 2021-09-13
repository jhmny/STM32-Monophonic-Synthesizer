/*
 * Codec.cpp
 *
 *  Created on: Sep 12, 2021
 *      Author: Joshua
 */

#include "Codec.h"

//#include "i2c.h"
//#include "gpio.h"

Codec::Codec() {
	// TODO Auto-generated constructor stub

}

Codec::~Codec() {
	// TODO Auto-generated destructor stub
}

uint8_t Codec::init(){
	uint8_t status = 0;
	HAL_GPIO_WritePin(GPIOD, CODEC_RESET_Pin, GPIO_PIN_SET);
	status += write(0x04, 0xaf);
	status += write(0x06, 0x07);
	status += write(0x02, 0x9e);

	return status;
}

uint8_t Codec::write(uint8_t reg, uint8_t val){
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write(&hi2c, AUDIO_I2C_ADDR, reg, 1, &val, sizeof(val), HAL_MAX_DELAY);
}

