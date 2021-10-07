/*
 * Codec.h
 *
 *  Created on: Sep 12, 2021
 *      Author: Joshua
 */

#ifndef SRC_CODEC_H_
#define SRC_CODEC_H_

#include "stdint.h"
#include <stdio.h>

class Codec {
public:
	Codec();
	virtual ~Codec();

	uint8_t init();
private:
	uint8_t write(uint8_t reg, uint8_t val);
};

#endif /* SRC_CODEC_H_ */