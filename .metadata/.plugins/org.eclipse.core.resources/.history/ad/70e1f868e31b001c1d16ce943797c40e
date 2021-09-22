/*
 * Synth.h
 *
 *  Created on: Sep 12, 2021
 *      Author: Joshua
 */

#ifndef SRC_SYNTH_H_
#define SRC_SYNTH_H_

#include <stdio.h>

#define WTB_LEN 1024
#define BUFF_LEN 8192
#define BUFF_LEN_HALF BUFF_LEN/2
#define SAMPLE_RATE 48000

class Synth {
public:
	Synth();
	virtual ~Synth();

	float oscWTBPointer = 0;
	float osc;
	float signal = 0;
	float pitch = 0;

	float calculateOscilator();
};

#endif /* SRC_SYNTH_H_ */
