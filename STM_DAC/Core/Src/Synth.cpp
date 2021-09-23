/*
 * Synth.cpp
 *
 *  Created on: Sep 12, 2021
 *      Author: Joshua
 */

#include "Synth.h"

//#include "wavetable.h"

Synth::Synth() {
	// TODO Auto-generated constructor stub

}

Synth::~Synth() {
	// TODO Auto-generated destructor stub
}

float Synth::calculateOscilator(){
	uint16_t a,b;
	float da, db;

	float oscWTBInc = WTB_LEN * (pitch) / SAMPLE_RATE;
	oscWTBPointer = oscWTBPointer + oscWTBInc;

	if (oscWTBPointer > WTB_LEN){
		oscWTBPointer = oscWTBPointer - WTB_LEN;
	}

	a = (int)oscWTBPointer;
	da = oscWTBPointer - a;
	b = a+1;

	db = b - oscWTBPointer;

	if (b>= WTB_LEN){
		b = 0;
	}
	osc = db * triangle[a] + da * triangle[b];

	signal = osc * 32767.0f;
	if (signal > 32767.0f){
		signal = 32767.0f;
	}
	if (signal < -32767.0f){
		signal = -32767.0f;
		}
return signal;
}