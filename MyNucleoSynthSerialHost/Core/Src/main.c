/* USER CODE BEGIN Header */
/**
  *					@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  *					@@@ Nucleo-144 PolySynthesizer Serial - GCC Version 1.0.1		@@@
  *					@@@ 4/6/20 by C.P.	For Casio									@@@
  *					@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
DAC_HandleTypeDef    DacHandle;
DAC_ChannelConfTypeDef sConfig;
TIM_MasterConfigTypeDef sMasterConfig;
TIM_HandleTypeDef  htim2, htim3, htim4, htim5, htim6, htim7, htim8, htim9;
TIM_HandleTypeDef  htim10, htim11, htim12, htim13, htim14;
RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
RCC_ClkInitTypeDef RCC_ClkInitStruct;
RCC_OscInitTypeDef RCC_OscInitStruct;

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define WRITE_READ_FLASH_ADDR 0x08000000 // Set memory to FLASH
#define WRITE_READ_SRAM_ADDR 0x20000000 // Set memory to SRAM
#define WRITE_READ_ADDR 0x40024000 // Set sequencer memory to BKPSSRAM

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int16_t delay_in = 0, delay_out = 500;
uint16_t counter[12], output, output1, output2, pwval, pwmval, modval;
uint8_t msgnum, midimsg, received_char, key, velocity, ctrl, data;
uint8_t wavesel, velsel, pwm, pwm2, mod, vcf, tun, det, sus, notepos, bend, param, patch;
uint8_t paramvalue[32], vhbtn = 0;
uint8_t voice = 0, n, i, j, y, r, c, d, e, f, g, h, k, m;
uint8_t chord, seqnote, triad2, triad3, triad4;
uint16_t lfo1rate, lfo1 = 63, lfo1cnt = 1, lfo1pol = 1;
uint16_t lfo2rate, lfo2 = 63, lfo2cnt = 1, lfo2pol = 1;
uint16_t lfo3rate, lfo3 = 63, lfo3cnt = 1, lfo3pol = 1;
uint16_t lfo4rate, lfo4 = 63, lfo4cnt = 1, lfo4pol = 1;
int8_t transpose, scale;
const uint32_t pitchtbl[] = {16384,
	15464,14596,13777,13004,12274,11585,10935,10321,9742,9195,8679,
	8192,7732,7298,6889,6502,6137,5793,5468,5161,4871,4598,4340,
	4096,3866,3649,3444,3251,3069,2896,2734,2580,2435,2299,2170,
	2048,1933,1825,1722,1625,1534,1448,1367,1290,1218,1149,1085,
	1024,967,912,861,813,767,724,683,645,609,575,542,
	512,483,456,431,406,384,362,342,323,304,287,271,
	256,242,228,215,203,192,181,171,161,152,144,136,
	128,121,114,108 ,102,96,91,85,81,76,72,68,64};
uint8_t chanstat[6] = {255,255,255,255,255,255};
uint8_t vcfadsr[6] = {0,0,0,0,0,0}, vcaadsr[6] = {0,0,0,0,0,0};
__IO uint32_t loadcount;
__IO uint32_t storecount;
float channel[12] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float vcfcutoff[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float vcacutoff[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float vcfkeyfollow[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float envkeyfollow[6] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
float summer = 0.0f, summer1 = 0.0f, summer2 = 0.0f, pbend = 0.0f;
float modlvl = 0.0f, pwmlvl = 0.0f, pwm2lvl = 0.0f, vcflvl = 0.0f, vcfval = 0.0f;
float vcfkflvl, envkflvl, oscmix, vcfreleaselvl = 0.000001f, vcareleaselvl = 0.000001f, resonance;
float vcfattackrate[6], vcfdecayrate[6], vcfsustainlvl[6], vcfreleaserate[6];
float vcfvellvl[6], vcavellvl[6], vcfenvlvl;
float vcfattack, vcfdecay, vcfsustain, vcfrelease;
float vcaattackrate[6], vcadecayrate[6], vcasustainlvl[6], vcareleaserate[6];
float vcaattack, vcadecay, vcasustain, vcarelease;
float delaybuffer[1000];

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void DAC_Config(void);
void TIM2_Config(uint16_t);
void TIM3_Config(uint16_t);
void TIM4_Config(uint16_t);
void TIM5_Config(uint16_t);
void TIM6_Config(uint16_t);
void TIM7_Config(uint16_t);
void TIM8_Config(uint16_t);
void TIM9_Config(uint16_t);
void TIM10_Config(uint16_t);
void TIM11_Config(uint16_t);
void TIM12_Config(uint16_t);
void TIM13_Config(uint16_t);
void TIM14_Config(uint16_t);
void SystemClock_Config(void);
void Error_Handler(void);
void CPU_CACHE_Enable(void);
void play_note(uint8_t, uint8_t);
void stop_note(uint8_t);
void play_slave(uint8_t, uint8_t);
void stop_slave(uint8_t);
void mixer(void);
float KarlsenLPF(float, float, float, uint8_t);
void envelope(void);
void MX_GPIO_Init(void);
void MakeSound(void);
void LocalMidiHandler(uint8_t, uint8_t);
void PrepOscs(void);
void UpdateLFOs(void);
void ProcessPitch(void);
void ProcessADSRs(void);
void AudioOutput(void);
void enable_backup_sram(void);
void writeBkpSram(uint32_t, uint8_t);
uint8_t readBkpSram(uint32_t);
void writeBkpSramWord(uint32_t, uint16_t);
uint16_t readBkpSramWord(uint32_t);
void InitPatch(void);
void GetPatch(uint32_t);
void PutPatch(uint32_t);
void ParamUpdate(uint8_t, uint8_t);
void Configure_USARTx(void);
void Configure_USARTy(void);
void SendToUSART(uint8_t);
void ProcessReceivedMidiDatas(void);
void SetLeds(uint8_t);
void SelfTest(void);

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
	/* Enable the CPU Cache */
	CPU_CACHE_Enable();

	/* STM32F7xx HAL library initialization */
	HAL_Init();

	/* Configure the system clock to 216 MHz */
	SystemClock_Config();

	/* Initialize all GPIOs */
	MX_GPIO_Init();
	
	/* Pause to ensure that the master and slave communicate */
	HAL_Delay(1000);
	
	/* Initialize serial communication */
	Configure_USARTx();
	Configure_USARTy();

	/* Configures the DAC for stereo output */
	DAC_Config();
	
	/* Enable the BB-SRAM */
	enable_backup_sram();
	
	/* Load the initial global system settings */
	param = 0;					/* Choose no param to edit (default is pitch bend) */
	sus = 0;						/* Set the sustain pedal to off */
	transpose = -20;			/* Set the transpose to none */

	/* Set initial values for continuous controllers */	
	paramvalue[0] = 64;			/* Set pitch bend to center */
	ParamUpdate(0, paramvalue[0]);
	paramvalue[1] = 0;			/* Set the modulation wheel to off */
	ParamUpdate(1, paramvalue[1]);
	paramvalue[2] = 64;			/* Set the master tuning to center */
	ParamUpdate(2, paramvalue[2]);
	
	/* Get the first patch loaded into the synth engine */
	InitPatch();
	GetPatch(0);
	
	/* Prepare the oscillators for use */
	PrepOscs();
	
	/* Start Timer 9 interrupts to trigger the mixer routine */
	TIM9_Config(3);

  /* USER CODE END 1 */
  
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    /* USER CODE END 3 */
  }
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

  /* USER CODE END Error_Handler_Debug */
}

void envelope(void)
{
	/* Process the pitch of the notes */
	ProcessPitch();
	
	/* Process the VCF/VCA ADSRs */
	ProcessADSRs();
}

void mixer(void)
{
	/* Process the waveforms for all voices */
	MakeSound();
	
	/* Process the final sound and play thru the DAC */
	AudioOutput();
	
	/* Update the LFOs */
	UpdateLFOs();
}

void AudioOutput(void)
{	
	/* Clear the sum of the oscillators */
	summer = 0.0f;
	
	/* Apply the VCA/VCF with key follow to all voices */
	for(i=0;i<6;i++)
	{
		channel[i] = channel[i] * (vcacutoff[i] * vcavellvl[i]);
		summer = summer + KarlsenLPF(channel[i], (vcfval * vcfenvlvl) * ((vcfcutoff[i] * vcfkeyfollow[i]) * vcfvellvl[i]), resonance, i);
	}
	
	/* Get the average of the sum */
	summer = summer / 6.0f;
	
	/* Process the delayed signal */
	delaybuffer[delay_in] = summer;
	delay_in++;
	if(delay_in == 1000)delay_in = 0;
	delay_out++;
	if(delay_out == 1000)delay_out = 0;
	
	/* Create the synth output */
	output1 = (uint16_t)2048.0f + (2047.0f * summer);
	output2 = (uint16_t)2048.0f + (2047.0f * delaybuffer[delay_out]);
	
	/* Set the DAC directly */
	HAL_DAC_SetValue(&DacHandle, DAC_CHANNEL_1, DAC_ALIGN_12B_R, output1);
	HAL_DAC_SetValue(&DacHandle, DAC_CHANNEL_2, DAC_ALIGN_12B_R, output2);
}

void PrepOscs(void)
{
	/* Cycle oscillator timers so there is no initial output spike */
	TIM14_Config(2048);
	TIM2_Config(2048);
	TIM3_Config(2048);
	TIM4_Config(2048);
	TIM5_Config(2048);
	TIM8_Config(2048);
	TIM6_Config(2048);
	TIM7_Config(2048);
	TIM10_Config(2048);
	TIM11_Config(2048);
	TIM12_Config(2048);
	TIM13_Config(2048);
	HAL_TIM_Base_Stop(&htim14);
	HAL_TIM_Base_Stop(&htim2);
	HAL_TIM_Base_Stop(&htim3);
	HAL_TIM_Base_Stop(&htim4);
	HAL_TIM_Base_Stop(&htim5);
	HAL_TIM_Base_Stop(&htim8);
	HAL_TIM_Base_Stop(&htim6);
	HAL_TIM_Base_Stop(&htim7);
	HAL_TIM_Base_Stop(&htim10);
	HAL_TIM_Base_Stop(&htim11);
	HAL_TIM_Base_Stop(&htim12);
	HAL_TIM_Base_Stop(&htim13);
}

void play_note(uint8_t note, uint8_t velocity)
{
	// If the note is playing already, just re-trigger it
	for(j=0;j<6;j++)
	{
		if(chanstat[j] == note)
		{
			// Load VCF/VCA ADS parameters.
			if(velsel == 1 | velsel == 3)
			{
				vcfvellvl[j] = ((float)(velocity) / 127.0f);
			}
			else
			{
				vcfvellvl[j] = 1.0f;
			}
			vcfsustainlvl[j] = vcfsustain;
			if(velsel >= 2)
			{
				vcavellvl[j] = ((float)(velocity) / 127.0f);
			}
			else
			{
				vcavellvl[j] = 1.0f;
			}
			vcasustainlvl[j] = vcasustain;
			
			// Set the VCF/VCA ADSR to attack state and cutoff level to zero.
			vcfcutoff[j] = 0.0f;
			vcfadsr[j] = 1;
			vcacutoff[j] = 0.0f;
			vcaadsr[j] = 1;
			return;
		}
	}	
	
	// Cycle thru available voices and assign the note to it, or steal from released voice. 
	for(j=0;j<6;j++)
	{
		if(vcfadsr[voice] == 4 | vcaadsr[voice] == 4 | chanstat[voice] == 255) // Voice is free or in released state?
		{
			// Load VCF/VCA ADS parameters.
			if(velsel == 1 | velsel == 3)
			{
				vcfvellvl[voice] = ((float)(velocity) / 127.0f);
			}
			else
			{
				vcfvellvl[voice] = 1.0f;
			}
			vcfsustainlvl[voice] = vcfsustain;
			if(velsel >= 2)
			{
				vcavellvl[voice] = ((float)(velocity) / 127.0f);
			}
			else
			{
				vcavellvl[voice] = 1.0f;
			}
			vcasustainlvl[voice] = vcasustain;
			
			// Set the VCF/VCA ADSR to attack state and cutoff level to zero.
			vcfcutoff[voice] = 0.0f;
			vcfadsr[voice] = 1;
			vcacutoff[voice] = 0.0f;
			vcaadsr[voice] = 1;
			
			chanstat[voice] = note; // Set the channel status to the note number playing
			
			// update the pitch of the voices oscillators.
			switch(voice)
			{
				case(0):
					TIM14_Config(pitchtbl[note + scale]);
					TIM6_Config(pitchtbl[note]);
					break;
				case(1):
					TIM2_Config(pitchtbl[note + scale]);
					TIM7_Config(pitchtbl[note]);
					break;
				case(2):
					TIM3_Config(pitchtbl[note + scale]);
					TIM10_Config(pitchtbl[note]);
					break;
				case(3):
					TIM4_Config(pitchtbl[note + scale]);
					TIM11_Config(pitchtbl[note]);
					break;
				case(4):
					TIM5_Config(pitchtbl[note + scale]);
					TIM12_Config(pitchtbl[note]);
					break;
				case(5):
					TIM8_Config(pitchtbl[note + scale]);
					TIM13_Config(pitchtbl[note]);
					break;
			}
			
			// Move to the next voice and return.
			voice++;
			if(voice > 5)
			{
				voice = 0;
			}
			return;
		}
		
		// Move to the next voice and continue searching.
		voice++;
		if(voice > 5)
		{
			voice = 0;
		}
		SetLeds(voice + 1);
	}
	/* If no voices available, then play the note on the slave board */
	play_slave(note, velocity);
}

void stop_note(uint8_t note)
{
	/* Find the voice that is playing the note and release it */
	for(n=0;n<6;n++)
	{
		if(note == chanstat[n]) // Is this the voice that is playing the note?
		{
			vcfadsr[n] = 4; // Set the voice VCF ADSR to release state
			vcaadsr[n] = 4; // Set the voice VCA ADSR to release state
			return;
		}	
	}
	/* If it wasn't the master board, assume it was the slave board */
	stop_slave(note);
}

void play_slave(uint8_t ps_note, uint8_t ps_velocity)
{
	SendToUSART(0x90);
	SendToUSART(ps_note);
	SendToUSART(ps_velocity);
}

void stop_slave(uint8_t ss_note)
{
	SendToUSART(0x80);
	SendToUSART(ss_note);
	SendToUSART(0x00);
}

void MakeSound(void)
{
	/* Get the timer values (sawtooth oscillators) into an array */
	counter[0] = __HAL_TIM_GetCounter(&htim14);
	counter[1] = __HAL_TIM_GetCounter(&htim2);
	counter[2] = __HAL_TIM_GetCounter(&htim3);
	counter[3] = __HAL_TIM_GetCounter(&htim4);
	counter[4] = __HAL_TIM_GetCounter(&htim5);
	counter[5] = __HAL_TIM_GetCounter(&htim8);
	counter[6] = __HAL_TIM_GetCounter(&htim6);
	counter[7] = __HAL_TIM_GetCounter(&htim7);
	counter[8] = __HAL_TIM_GetCounter(&htim10);
	counter[9] = __HAL_TIM_GetCounter(&htim11);
	counter[10] = __HAL_TIM_GetCounter(&htim12);
	counter[11] = __HAL_TIM_GetCounter(&htim13);
	
	if(wavesel) /* Fall thru if wavsel = 0, all oscillators to sawtooth */
	{
		if(wavesel > 0)
		{
			/* Calculate the pwm value for the upper oscillators square wave */
			pwmval = pwval << 1;
		
			/* Apply the LFO to the pwm value before generating the square wave */
			pwmval = pwmval + (pwm * pwmlvl);
		
			/* Generate square waves from sawtooth waves */
			for(i=0;i<6;i++)
			{
				if(counter[i] > pwmval)
				{
					counter[i] = 506;
				}
				else
				{
					counter[i] = 0;
				}
			}
		}
		
		if(wavesel > 1)
		{
			/* Calculate the pwm value for the lower oscillators square wave */
			pwmval = pwval << 1;
		
			/* Apply the LFO to the pwm value before generating the square wave */
			pwmval = pwmval + (pwm2 * pwm2lvl);
		
			/* Generate square waves from sawtooth waves */
			for(i=6;i<12;i++)
			{
				if(counter[i] > pwmval)
				{
					counter[i] = 506;
				}
				else
				{
					counter[i] = 0;
				}
			}
		}	
	}

	/* Convert waveforms to floating point and apply oscillator mix */
	for(i=0;i<6;i++)
	{
		channel[i] = oscmix * (-1.0f + (((float)counter[i] / 252.0f)));
		channel[i] = channel[i] + ((1.0f - oscmix) * ((-1.0f + (((float)counter[i + 6] / 252.0f)))));
	}
}

void UpdateLFOs(void)
{
	/* Update the MOD LFO */
	lfo1cnt--;
	if(lfo1cnt == 0)
	{
		lfo1 = lfo1 + lfo1pol;
		if(lfo1 == 127 | lfo1 == 0)
		{
			lfo1pol = -lfo1pol;
		}
		lfo1cnt = lfo1rate;
	}
	
	modlvl = 1.0f - (((float)(lfo1) / 64.0f));
	
	/* Update the PWM LFO */
	lfo2cnt--;
	if(lfo2cnt == 0)
	{
		lfo2 = lfo2 + lfo2pol;
		if(lfo2 == 127 | lfo2 == 0)
		{
			lfo2pol = -lfo2pol;
		}
		lfo2cnt = lfo2rate;
	}
	
	pwmlvl = 1.0f - (((float)(lfo2)) / 64.0f);
	
	/* Update the VCF LFO */
	lfo3cnt--;
	if(lfo3cnt == 0)
	{
		lfo3 = lfo3 + lfo3pol;
		if(lfo3 == 127 | lfo3 == 0)
		{
			lfo3pol = -lfo3pol;
		}
		lfo3cnt = lfo3rate;
	}
	
	vcflvl = 1.0f - (((float)(lfo3) / 127.0f));
	
	/* Update the PWM2 LFO */
	lfo4cnt--;
	if(lfo4cnt == 0)
	{
		lfo4 = lfo4 + lfo4pol;
		if(lfo4 == 127 | lfo4 == 0)
		{
			lfo4pol = -lfo4pol;
		}
		lfo4cnt = lfo4rate;
	}

	pwm2lvl = 1.0f - (((float)(lfo4) / 64.0f));
}

void ProcessPitch(void)
{
	/* Process the pitch of the notes, start with system tuning value */
	modval = 506;
	
	/* Apply the LFO to modulate all the oscillators */
	modval = modval + (mod * modlvl);
	
	/* Calculate the pitch bend value */
	pbend = 1.0f - (((float)bend / 64.0f));
	
	/* Add in the pitch bend and tuning */
	modval = modval + (int8_t)(pbend * 56.0f) + (63 - tun);
	
	/* Calculate the vcf LFO mod value */
	vcfval = (1.0f - ((float)(vcf) / 127.0f)) + (((float)(vcf) / 127.0f) * vcflvl);
	
	/* Update all of the oscillators */
	TIM14->ARR = modval;
	TIM2->ARR = modval;
	TIM3->ARR = modval;
	TIM4->ARR = modval;
	TIM5->ARR = modval;
	TIM8->ARR = modval;
	/* Add in the de-tune for lower oscillators */
	TIM6->ARR = modval + det;
	TIM7->ARR = modval + det;
	TIM10->ARR = modval + det;
	TIM11->ARR = modval + det;
	TIM12->ARR = modval + det;
	TIM13->ARR = modval + det;
}

void ProcessADSRs(void)
{
	/* Process the VCF/VCA ADSR and apply to all voices */
	for(y=0;y<6;y++)
	{
		if(chanstat[y] != 255) // Is a note currently playing?
		{
			/* Calculate the key follow values based on the key follow levels */
			vcfkeyfollow[y] = (1 - vcfkflvl) + (((float)(chanstat[y]) / 76.0f) * vcfkflvl);
			envkeyfollow[y] = (1 - envkflvl) + (((float)(chanstat[y]) / 76.0f) * envkflvl);
			
			/* Update the state of the VCF ADSR */
			switch(vcfadsr[y])
			{
				case (0): // Idle state
					break;
				case (1): // Attack state
					// Calculate the VCF attack rate
					vcfattackrate[y] =  1.0f / vcfattack;
					// Ramp up the cutoff by incrementing by VCF attack rate contoured with key follow
					vcfcutoff[y] = vcfcutoff[y] + (vcfattackrate[y] * envkeyfollow[y]);
					if(vcfcutoff[y] >= 1.0f) // Attack level reached yet?
					{
						vcfcutoff[y] = 1.0f;
						vcfadsr[y] = 2; // switch to decay state
					}
					break;
				case (2): // Decay state
					// Calculate the VCF decay rate
					vcfdecayrate[y] =  (1.0f - vcfsustainlvl[y]) / vcfdecay;
					// Ramp down the cutoff by incrementing by VCF decay rate contoured with key follow
					vcfcutoff[y] = vcfcutoff[y] - (vcfdecayrate[y] * envkeyfollow[y]);
					if(vcfcutoff[y] <= vcfsustainlvl[y]) // Decay level reached yet?
					{
						vcfcutoff[y] = vcfsustainlvl[y] + vcfreleaselvl; // ensure sustainlvl > releaselvl
						vcfadsr[y] = 3; // switch to sustain state
					}
					break;
				case (3): // Sustain state
					// Just hold the VCF cutoff value steady until note is released
					break;
				case (4): // Release state
					// Calculate the VCF release rate
					vcfreleaserate[y] =  vcfcutoff[y] / vcfrelease;
					// Ramp down the cutoff by incrementing by VCF release rate
					vcfcutoff[y] = vcfcutoff[y] - (vcfreleaserate[y] * envkeyfollow[y]);
					if(vcfcutoff[y] <= vcfreleaselvl) // Release level reached yet?
					{
						vcfcutoff[y] = 0.0f;
						vcfadsr[y] = 0; // switch to idle state
						chanstat[y] = 255; // Set voice to no note playing
					}
					break;
				}
			
				/* Update the state of the VCA ADSR */
				switch(vcaadsr[y])
				{
					case (0): // Idle state
						break;
					case (1): // Attack state
						// Calculate the VCA attack rate
						vcaattackrate[y] =  1.0f / vcaattack;
						// Ramp up the amplitude by incrementing by VCA attack rate contoured with key follow
						vcacutoff[y] = vcacutoff[y] + (vcaattackrate[y] * envkeyfollow[y]);
						if(vcacutoff[y] >= 1.0f) // Attack level reached yet?
						{
							vcacutoff[y] = 1.0f;
							vcaadsr[y] = 2; // switch to decay state
						}
						break;
					case (2): // Decay state
						// Calculate the VCA decay rate
						vcadecayrate[y] =  (1.0f - vcasustainlvl[y]) / vcadecay;
						// Ramp down the cutoff by incrementing by VCA decay rate contoured with key follow
						vcacutoff[y] = vcacutoff[y] - (vcadecayrate[y] * envkeyfollow[y]);
						if(vcacutoff[y] <= vcasustainlvl[y]) // Decay level reached yet?
						{
							vcacutoff[y] = vcasustainlvl[y] + vcareleaselvl; // ensure sustainlvl > releaselvl
							vcaadsr[y] = 3; // switch to sustain state
						}
						break;
					case (3): // Sustain state
						// Just hold the VCA cutoff value steady until note is released
						break;
					case (4): // Release state
						// Calculate the VCA release rate
						vcareleaserate[y] =  vcacutoff[y] / vcarelease;
						// Ramp down the cutoff by incrementing by VCA release rate
						vcacutoff[y] = vcacutoff[y] - (vcareleaserate[y] * envkeyfollow[y]);
						if(vcacutoff[y] <= vcareleaselvl) // Release level reached yet?
						{
							vcacutoff[y] = 0.0f;
							vcaadsr[y] = 0; // switch to idle state
							chanstat[y] = 255; // Set voice to no note playing
						}
						break;
					}
		}
	}
}

// Karlsen 24dB Filter
// b_f = frequency 0..1
// b_q = resonance 0..5

float KarlsenLPF(float signal, float freq, float res, uint8_t m)
{
	static float b_inSH[6], b_in[6], b_f[6], b_q[6], b_fp[6], pole1[6], pole2[6], pole3[6], pole4[6];
	b_inSH[m] = signal;
	b_in[m] = signal;
	if(freq > 1.0f)freq = 1.0f;
	if(freq < 0.0f)freq = 0.0f;
	b_f[m] = freq;
	b_q[m] = res;
	uint8_t b_oversample = 0;
		
	while (b_oversample < 2)
	{	
		//2x oversampling
		float prevfp;
		prevfp = b_fp[m];
		if (prevfp > 1.0f) {prevfp = 1.0f;}	// Q-limiter

		b_fp[m] = (b_fp[m] * 0.418f) + ((b_q[m] * pole4[m]) * 0.582f);	// dynamic feedback
		float intfp;
		intfp = (b_fp[m] * 0.36f) + (prevfp * 0.64f);	// feedback phase
		b_in[m] =	b_inSH[m] - intfp;	// inverted feedback	

		pole1[m] = (b_in[m] * b_f[m]) + (pole1[m] * (1.0f - b_f[m]));	// pole 1
		if (pole1[m] > 1.0f) {pole1[m] = 1.0f;} else if (pole1[m] < -1.0f) {pole1[m] = -1.0f;} // pole 1 clipping
		pole2[m] = (pole1[m] * b_f[m]) + (pole2[m] * (1 - b_f[m]));	// pole 2
		pole3[m] = (pole2[m] * b_f[m]) + (pole3[m] * (1 - b_f[m]));	// pole 3
		pole4[m] = (pole3[m] * b_f[m]) + (pole4[m] * (1 - b_f[m]));	// pole 4

		b_oversample++;
	}
	return pole4[m];
}

void ProcessReceivedMidiDatas(void)
{			
			uint8_t chan = midimsg & 0xf;
			uint8_t msgtype = midimsg & 0xf0;
		
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

	/* Send parameter edit data to slave board */
	SendToUSART(0xF0);
	SendToUSART(m_param);
	SendToUSART(m_data);
}

void ParamUpdate(uint8_t u_param, uint8_t u_data)
{
	switch(u_param)
	{
		case (0):  // Pitch Wheel
			bend = u_data;
			break;
		case (1): // Modulation Wheel
			if(u_data >= 64)
			{
				mod = (u_data - 64) >> 1;
			}
			break;
		case (2): // Tuning
			tun = u_data;
			break;
		case (3): // Wave Select
			wavesel = u_data >> 5;
			break;
		case (4): // OSC Mix
			oscmix = (((float)(u_data)) * 0.007874f);
			break;
		case (5): // De-Tune 
			det = u_data >> 4;
			break;
		case (6): // Scale
			scale = (u_data - 64) >> 2;
			break;
		case (7): // Resonance
			resonance = (((float)(u_data)) * 0.007874f * 4.0f);
			break;
		case (8): // Pulse Width Value
			pwval = u_data;
			break;
		case (9): // VCF Attack
			vcfattack = (((float)(u_data)) * 10.0f);
			break;
		case (10): // VCF Decay
			vcfdecay = (((float)(u_data)) * 10.0f);
			break;
		case (11): // VCF Sustain
			vcfsustain = (((float)(u_data)) * 0.007874f);
			break;
		case (12): // VCF Release
			vcfrelease = (((float)(u_data)) * 10.0f);
			break;
		case (13): // VCA Attack
			vcaattack = (((float)(u_data)) * 10.0f);
			break;
		case (14): // VCA Decay
			vcadecay = (((float)(u_data)) * 10.0f);
			break;
		case (15): // VCA Sustain
			vcasustain = (((float)(u_data)) * 0.007874f);
			break;
		case (16): // VCA Release
			vcarelease = (((float)(u_data)) * 10.0f);
			break;
		case (17): // VCF Follow Level
			vcfkflvl = (((float)(u_data)) * 0.007874f);
			break;
		case (18): // ENV Follow Level
			envkflvl = (((float)(u_data)) * 0.007874f);
			break;
		case (19): // Velocity Select
			velsel = u_data >> 5;
			break;
		case (20): // VCF Envelope Level
			vcfenvlvl = (((float)(u_data)) * 0.007874f);
			break;
		case (21): // Mod LFO rate
			lfo1rate = (128 - u_data) << 2; 
			break;
		case (22): // Pwm LFO rate
			lfo2rate = (128 - u_data) << 2;
			break;
		case (23): // Pwm2 LFO rate
			lfo4rate = (128 - u_data) << 2;
			break;
		case (24): // Vcf LFO rate
			lfo3rate = (128 - u_data) << 2;
			break;
		case (25): // VCF LFO Mod level
			vcf = u_data;
			break;
		case (26): // PWM Level
			pwm = u_data;
			break;
		case (27): // PWM2 Level
			pwm2 = u_data;
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
}

void SetLeds(uint8_t ledvalue)
{
	switch (ledvalue)
	{
		case (0):
			HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin|LD1_Pin, GPIO_PIN_RESET);
			break;
		case (1):
			HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_RESET);
			break;
		case (2):
			HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD1_Pin, GPIO_PIN_RESET);
			break;
		case (3):
			HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_RESET);
			break;
		case (4):
			HAL_GPIO_WritePin(GPIOB, LD3_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, LD2_Pin|LD1_Pin, GPIO_PIN_RESET);
			break;
		case (5):
			HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, LD2_Pin, GPIO_PIN_RESET);
			break;
		case (6):
			HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, LD1_Pin, GPIO_PIN_RESET);
			break;
		case (7):
			HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin|LD1_Pin, GPIO_PIN_SET);
			break;
	}		
}

/**
  * @brief  This function configures USARTx Instance.
  * @note   This function is used to :
  *         -1- Enable GPIO clock and configures the USART pins.
  *         -2- NVIC Configuration for USART interrupts.
  *         -3- Enable the USART peripheral clock and clock source.
  *         -4- Configure USART functional parameters.
  *         -5- Enable USART.
  * @note   Peripheral configuration is minimal configuration from reset values.
  *         Thus, some useless LL unitary functions calls below are provided as
  *         commented examples - setting is default configuration from reset.
  * @param  None
  * @retval None
  */
void Configure_USARTx(void)
{

  /* (1) Enable GPIO clock and configures the USART pins *********************/

  /* Enable the peripheral clock of GPIO Port */
  USARTx_GPIO_CLK_ENABLE();

  /* Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up */
  LL_GPIO_SetPinMode(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_MODE_ALTERNATE);
  USARTx_SET_TX_GPIO_AF();
  LL_GPIO_SetPinSpeed(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(USARTx_TX_GPIO_PORT, USARTx_TX_PIN, LL_GPIO_PULL_UP);

  /* Configure Rx Pin as : Alternate function, High Speed, Push pull, Pull up */
  LL_GPIO_SetPinMode(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_MODE_ALTERNATE);
  USARTx_SET_RX_GPIO_AF();
  LL_GPIO_SetPinSpeed(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(USARTx_RX_GPIO_PORT, USARTx_RX_PIN, LL_GPIO_PULL_UP);

  /* (2) NVIC Configuration for USART interrupts */
  /*  - Set priority for USARTx_IRQn */
  /*  - Enable USARTx_IRQn */
  NVIC_SetPriority(USARTx_IRQn, 0);  
  NVIC_EnableIRQ(USARTx_IRQn);

  /* (3) Enable USART peripheral clock and clock source ***********************/
  USARTx_CLK_ENABLE();

  /* Set clock source */
  USARTx_CLK_SOURCE();

  /* (4) Configure USART functional parameters ********************************/
  
  /* Disable USART prior modifying configuration registers */
  /* Note: Commented as corresponding to Reset value */
  // LL_USART_Disable(USARTx_INSTANCE);

  /* TX/RX direction */
  LL_USART_SetTransferDirection(USARTx_INSTANCE, LL_USART_DIRECTION_TX_RX);

  /* 8 data bit, 1 start bit, 1 stop bit, no parity */
  LL_USART_ConfigCharacter(USARTx_INSTANCE, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

  /* No Hardware Flow control */
  /* Reset value is LL_USART_HWCONTROL_NONE */
  // LL_USART_SetHWFlowCtrl(USARTx_INSTANCE, LL_USART_HWCONTROL_NONE);

  /* Oversampling by 16 */
  /* Reset value is LL_USART_OVERSAMPLING_16 */
  //LL_USART_SetOverSampling(USARTx_INSTANCE, LL_USART_OVERSAMPLING_16);

  /* Set Baudrate to 921600 using APB frequency set to 216000000/APB_Div Hz */
  /* Frequency available for USART peripheral can also be calculated through LL RCC macro */
  /* Ex :
      Periphclk = LL_RCC_GetUSARTClockFreq(Instance); or LL_RCC_GetUARTClockFreq(Instance); depending on USART/UART instance
  
      In this example, Peripheral Clock is expected to be equal to 216000000/APB_Div Hz => equal to SystemCoreClock/APB_Div
  */
  LL_USART_SetBaudRate(USARTx_INSTANCE, SystemCoreClock/APB_Div, LL_USART_OVERSAMPLING_16, 115200); 

  /* (5) Enable USART *********************************************************/
  LL_USART_Enable(USARTx_INSTANCE);

  /* Enable RXNE and Error interrupts */
  LL_USART_EnableIT_RXNE(USARTx_INSTANCE);
  LL_USART_EnableIT_ERROR(USARTx_INSTANCE);
}

/**
  * @brief  This function configures USARTy Instance.
  * @note   This function is used to :
  *         -1- Enable GPIO clock and configures the USART pins.
  *         -2- NVIC Configuration for USART interrupts.
  *         -3- Enable the USART peripheral clock and clock source.
  *         -4- Configure USART functional parameters.
  *         -5- Enable USART.
  * @note   Peripheral configuration is minimal configuration from reset values.
  *         Thus, some useless LL unitary functions calls below are provided as
  *         commented examples - setting is default configuration from reset.
  * @param  None
  * @retval None
  */
void Configure_USARTy(void)
{

  /* (1) Enable GPIO clock and configures the USART pins *********************/

  /* Enable the peripheral clock of GPIO Port */
  USARTy_GPIO_CLK_ENABLE();

  /* Configure Tx Pin as : Alternate function, High Speed, Push pull, Pull up */
  LL_GPIO_SetPinMode(USARTy_TX_GPIO_PORT, USARTy_TX_PIN, LL_GPIO_MODE_ALTERNATE);
  USARTy_SET_TX_GPIO_AF();
  LL_GPIO_SetPinSpeed(USARTy_TX_GPIO_PORT, USARTy_TX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(USARTy_TX_GPIO_PORT, USARTy_TX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(USARTy_TX_GPIO_PORT, USARTy_TX_PIN, LL_GPIO_PULL_UP);

  /* Configure Rx Pin as : Alternate function, High Speed, Push pull, Pull up */
  LL_GPIO_SetPinMode(USARTy_RX_GPIO_PORT, USARTy_RX_PIN, LL_GPIO_MODE_ALTERNATE);
  USARTy_SET_RX_GPIO_AF();
  LL_GPIO_SetPinSpeed(USARTy_RX_GPIO_PORT, USARTy_RX_PIN, LL_GPIO_SPEED_FREQ_HIGH);
  LL_GPIO_SetPinOutputType(USARTy_RX_GPIO_PORT, USARTy_RX_PIN, LL_GPIO_OUTPUT_PUSHPULL);
  LL_GPIO_SetPinPull(USARTy_RX_GPIO_PORT, USARTy_RX_PIN, LL_GPIO_PULL_UP);

  /* (2) NVIC Configuration for USART interrupts */
  /*  - Set priority for USARTy_IRQn */
  /*  - Enable USARTy_IRQn */
  NVIC_SetPriority(USARTy_IRQn, 0);
  NVIC_EnableIRQ(USARTy_IRQn);

  /* (3) Enable USART peripheral clock and clock source ***********************/
  USARTy_CLK_ENABLE();

  /* Set clock source */
  USARTy_CLK_SOURCE();

  /* (4) Configure USART functional parameters ********************************/

  /* Disable USART prior modifying configuration registers */
  /* Note: Commented as corresponding to Reset value */
  // LL_USART_Disable(USARTy_INSTANCE);

  /* TX/RX direction */
  LL_USART_SetTransferDirection(USARTy_INSTANCE, LL_USART_DIRECTION_TX_RX);

  /* 8 data bit, 1 start bit, 1 stop bit, no parity */
  LL_USART_ConfigCharacter(USARTy_INSTANCE, LL_USART_DATAWIDTH_8B, LL_USART_PARITY_NONE, LL_USART_STOPBITS_1);

  /* No Hardware Flow control */
  /* Reset value is LL_USART_HWCONTROL_NONE */
  // LL_USART_SetHWFlowCtrl(USARTy_INSTANCE, LL_USART_HWCONTROL_NONE);

  /* Oversampling by 16 */
  /* Reset value is LL_USART_OVERSAMPLING_16 */
  //LL_USART_SetOverSampling(USARTy_INSTANCE, LL_USART_OVERSAMPLING_16);

  /* Set Baudrate to 921600 using APB frequency set to 216000000/APB_Div Hz */
  /* Frequency available for USART peripheral can also be calculated through LL RCC macro */
  /* Ex :
      Periphclk = LL_RCC_GetUSARTClockFreq(Instance); or LL_RCC_GetUARTClockFreq(Instance); depending on USART/UART instance

      In this example, Peripheral Clock is expected to be equal to 216000000/APB_Div Hz => equal to SystemCoreClock/APB_Div
  */
  LL_USART_SetBaudRate(USARTy_INSTANCE, SystemCoreClock/APB_Div, LL_USART_OVERSAMPLING_16, 921600);

  /* (5) Enable USART *********************************************************/
  LL_USART_Enable(USARTy_INSTANCE);

  /* Enable RXNE and Error interrupts */
  LL_USART_EnableIT_RXNE(USARTy_INSTANCE);
  LL_USART_EnableIT_ERROR(USARTy_INSTANCE);
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow : 
  *            System Clock source            = PLL (HSI)
  *            SYSCLK(Hz)                     = 216000000
  *            HCLK(Hz)                       = 216000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 4
  *            HSI Frequency(Hz)              = 16000000
  *            PLL_M                          = 8
  *            PLL_N                          = 216
  *            PLL_P                          = 2
  *            PLL_Q                          = 9
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 7
  * @param  None
  * @retval None
  */
void SystemClock_Config(void)
{  
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /**Initializes the CPU, AHB and APB busses clocks */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16; // Variable +/- 50khz steps from 0 to 31
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 9;
  if(HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Activate the OverDrive to reach the 216 Mhz Frequency */
  if(HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  
  /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
     clocks dividers */
  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;
  if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    Error_Handler();
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
  PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /* Configure the Systick interrupt time */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  /* Configure the Systick */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

void DAC_Config(void)
{
	DacHandle.Instance = DACx;
	
  if (HAL_DAC_Init(&DacHandle) != HAL_OK)
  {
    Error_Handler();
  }

  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;

  if (HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DACx_CHANNEL) != HAL_OK)
  {
    Error_Handler();
  }
	
	if (HAL_DAC_ConfigChannel(&DacHandle, &sConfig, DACy_CHANNEL) != HAL_OK)
  {
    Error_Handler();
  }

  if (HAL_DAC_Start(&DacHandle, DACx_CHANNEL) != HAL_OK)
  {
    Error_Handler();
  }
	
	if (HAL_DAC_Start(&DacHandle, DACy_CHANNEL) != HAL_OK)
  {
    Error_Handler();
  }
}

void enable_backup_sram(void)
{
    /*DBP : Enable access to Backup domain */
    HAL_PWR_EnableBkUpAccess();
    /*PWREN : Enable backup domain access  */
    __HAL_RCC_PWR_CLK_ENABLE();
    /*BRE : Enable backup regulator
      BRR : Wait for backup regulator to stabilize */
    HAL_PWREx_EnableBkUpReg();
		/* Enable clock to BKPSRAM */
		__HAL_RCC_BKPSRAM_CLK_ENABLE();
}

void writeBkpSram(uint32_t l_addr, uint8_t l_data)
{
  /* Pointer write on specific location of backup SRAM */
  *(__IO uint8_t *) (WRITE_READ_ADDR + l_addr) = l_data;
}

uint8_t readBkpSram(uint32_t l_addr)
{
	uint8_t i_retval;
	
  /* Pointer write from specific location of backup SRAM */
  i_retval =  *(__IO uint8_t *) (WRITE_READ_ADDR + l_addr);
	
  return i_retval;
}

void writeBkpSramWord(uint32_t l_addr_w, uint16_t l_data_w)
{
  /* Pointer write on specific location of backup SRAM */
  *(__IO uint16_t *) (WRITE_READ_ADDR + l_addr_w) = l_data_w;
}

uint16_t readBkpSramWord(uint32_t l_addr_w)
{
	uint16_t i_retval_w;
	
  /* Pointer write from specific location of backup SRAM */
  i_retval_w =  *(__IO uint16_t *) (WRITE_READ_ADDR + l_addr_w);
	
  return i_retval_w;
}

void InitPatch(void)
{	
	/* Restore the default patch */
	paramvalue[0] = 64;			/* Set pitch bend to center */
	paramvalue[1] = 0;			/* Set the modulation wheel to off */
	paramvalue[2] = 64;			/* Set the master tuning to center */
	paramvalue[3] = 0;			/* Set the upper and lower waveforms to sawtooth */
	paramvalue[4] = 64;			/* Set oscillator mix to center */
	paramvalue[5] = 16;			/* Set the de-tune to 16 */
	paramvalue[6] = 64;			/* Set scale to no offset for upper oscillators */
	paramvalue[7] = 31;			/* Set resonance to 31 */
	paramvalue[8] = 127; 		/* Set the default PW value to 50% */
	paramvalue[9] = 0; 			/* Set VCF attack time */
	paramvalue[10] = 30;		/* Set VCF decay time */
	paramvalue[11] = 28;		/* Set VCF sustain level */
	paramvalue[12] = 8;			/* Set VCF release time */
	paramvalue[13] = 0;			/* Set VCA attack time */
	paramvalue[14] = 20;		/* Set VCA decay time */
	paramvalue[15] = 127;		/* Set VCA sustain level */
	paramvalue[16] = 8;			/* Set VCA release time */
	paramvalue[17] = 64;		/* Set VCF keyboard follow level to half */
	paramvalue[18] = 64;		/* Set ENV keyboard follow level to half */
	paramvalue[19] = 48;		/* Set Velocity to affect VCF only */
	paramvalue[20] = 127;		/* Set VCF envelope level to full */
	paramvalue[21] = 116;		/* Set MOD LFO rate */
	paramvalue[22] = 64;		/* Set PWM LFO rate */
	paramvalue[23] = 32;		/* Set PWM2 LFO rate */
	paramvalue[24] = 120;		/* Set VCF LFO rate */
	paramvalue[25] = 0;			/* Set VCF level to zero */
	paramvalue[26] = 0;			/* Set PWM level to zero */
	paramvalue[27] = 0;			/* Set PWM2 level to zero */
	paramvalue[28] = 0;			/* Un-assigned */
	paramvalue[29] = 0;			/* Un-assigned */
	paramvalue[30] = 0;			/* Un-assigned */
	paramvalue[31] = 0;			/* Un-assigned */
	
	PutPatch(0);
}

void GetPatch(uint32_t patchnumber)
{
	patchnumber = patchnumber << 5;
	
	/* Load the patch from RAM and populate the synth engine*/
	for(loadcount=3;loadcount<28;loadcount++)
	{
		paramvalue[loadcount] = readBkpSram(loadcount + patchnumber);
		ParamUpdate(loadcount, paramvalue[loadcount]);
	}
}

void PutPatch(uint32_t patchnumber)
{	
	patchnumber = patchnumber << 5;
	
	/* Save the patch to RAM */
	for(storecount=0;storecount<32;storecount++)
	{
		writeBkpSram(storecount + patchnumber, paramvalue[storecount]);
	}
}

void TIM2_Config(uint16_t period)
{
  htim2.Instance = TIM2;

  htim2.Init.Period            = 511;
  htim2.Init.Prescaler         = period;
  htim2.Init.ClockDivision     = 0;
  htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim2.Init.RepetitionCounter = 0;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim2);

  HAL_TIM_Base_Start(&htim2);
}

void TIM3_Config(uint16_t period)
{
  htim3.Instance = TIM3;

  htim3.Init.Period            = 511;
  htim3.Init.Prescaler         = period;
  htim3.Init.ClockDivision     = 0;
  htim3.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim3.Init.RepetitionCounter = 0;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim3);

  HAL_TIM_Base_Start(&htim3);
}

void TIM4_Config(uint16_t period)
{
  htim4.Instance = TIM4;

  htim4.Init.Period            = 511;
  htim4.Init.Prescaler         = period;
  htim4.Init.ClockDivision     = 0;
  htim4.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim4.Init.RepetitionCounter = 0;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim4);

  HAL_TIM_Base_Start(&htim4);
}

void TIM5_Config(uint16_t period)
{
  htim5.Instance = TIM5;

  htim5.Init.Period            = 511;
  htim5.Init.Prescaler         = period;
  htim5.Init.ClockDivision     = 0;
  htim5.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim5.Init.RepetitionCounter = 0;
	htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim5);

  HAL_TIM_Base_Start(&htim5);
}

void TIM8_Config(uint16_t period)
{
  htim8.Instance = TIM8;

  htim8.Init.Period            = 511;
  htim8.Init.Prescaler         = period;
  htim8.Init.ClockDivision     = 0;
  htim8.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim8.Init.RepetitionCounter = 0;
	htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim8);

  HAL_TIM_Base_Start(&htim8);
}

void TIM6_Config(uint16_t period)
{
  htim6.Instance = TIM6;

  htim6.Init.Period            = 511;
  htim6.Init.Prescaler         = period;
  htim6.Init.ClockDivision     = 0;
  htim6.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim6.Init.RepetitionCounter = 0;
	htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim6);

  HAL_TIM_Base_Start(&htim6);
}

void TIM7_Config(uint16_t period)
{
  htim7.Instance = TIM7;

  htim7.Init.Period            = 511;
  htim7.Init.Prescaler         = period;
  htim7.Init.ClockDivision     = 0;
  htim7.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim7.Init.RepetitionCounter = 0;
	htim7.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim7);

  HAL_TIM_Base_Start(&htim7);
}

void TIM10_Config(uint16_t period)
{
  htim10.Instance = TIM10;

  htim10.Init.Period            = 511;
  htim10.Init.Prescaler         = period;
  htim10.Init.ClockDivision     = 0;
  htim10.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim10.Init.RepetitionCounter = 0;
	htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim10);

  HAL_TIM_Base_Start(&htim10);
}

void TIM11_Config(uint16_t period)
{
  htim11.Instance = TIM11;

  htim11.Init.Period            = 511;
  htim11.Init.Prescaler         = period;
  htim11.Init.ClockDivision     = 0;
  htim11.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim11.Init.RepetitionCounter = 0;
	htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim11);

  HAL_TIM_Base_Start(&htim11);
}

void TIM12_Config(uint16_t period)
{
  htim12.Instance = TIM12;

  htim12.Init.Period            = 511;
  htim12.Init.Prescaler         = period;
  htim12.Init.ClockDivision     = 0;
  htim12.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim12.Init.RepetitionCounter = 0;
	htim12.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim12);

  HAL_TIM_Base_Start(&htim12);
}

void TIM13_Config(uint16_t period)
{
  htim13.Instance = TIM13;

  htim13.Init.Period            = 511;
  htim13.Init.Prescaler         = period;
  htim13.Init.ClockDivision     = 0;
  htim13.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim13.Init.RepetitionCounter = 0;
	htim13.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim13);

  HAL_TIM_Base_Start(&htim13);
}

void TIM14_Config(uint16_t period)
{
  htim14.Instance = TIM14;

  htim14.Init.Period            = 511;
  htim14.Init.Prescaler         = period;
  htim14.Init.ClockDivision     = 0;
  htim14.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim14.Init.RepetitionCounter = 0;
	htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim14);

  HAL_TIM_Base_Start(&htim14);
}

void TIM9_Config(uint16_t period)
{
  htim9.Instance = TIM9;

  htim9.Init.Period            = 511;
  htim9.Init.Prescaler         = period;
  htim9.Init.ClockDivision     = 0;
  htim9.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim9.Init.RepetitionCounter = 0;
	htim9.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim9);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;

  HAL_TIMEx_MasterConfigSynchronization(&htim9, &sMasterConfig);

  HAL_TIM_Base_Start_IT(&htim9);
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	/* Run the Mixer routine */
	mixer();
}

void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();

  /*Configure GPIO pin : User_Blue_Button_Pin */
  GPIO_InitStruct.Pin = User_Blue_Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(User_Blue_Button_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_MDC_Pin RMII_RXD0_Pin RMII_RXD1_Pin */
  GPIO_InitStruct.Pin = RMII_MDC_Pin|RMII_RXD0_Pin|RMII_RXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_REF_CLK_Pin RMII_MDIO_Pin RMII_CRS_DV_Pin */
  GPIO_InitStruct.Pin = RMII_REF_CLK_Pin|RMII_MDIO_Pin|RMII_CRS_DV_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : RMII_TXD1_Pin */
  GPIO_InitStruct.Pin = RMII_TXD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(RMII_TXD1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LD3_Pin LD2_Pin LD1_Pin */
  GPIO_InitStruct.Pin = LD3_Pin|LD2_Pin|LD1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_PowerSwitchOn_Pin */
  GPIO_InitStruct.Pin = USB_PowerSwitchOn_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_PowerSwitchOn_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_OverCurrent_Pin */
  GPIO_InitStruct.Pin = USB_OverCurrent_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(USB_OverCurrent_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : STLK_RX_Pin STLK_TX_Pin */
  GPIO_InitStruct.Pin = STLK_RX_Pin|STLK_TX_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : RMII_TX_EN_Pin RMII_TXD0_Pin */
  GPIO_InitStruct.Pin = RMII_TX_EN_Pin|RMII_TXD0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF11_ETH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LD3_Pin|LD2_Pin|LD1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_PowerSwitchOn_GPIO_Port, USB_PowerSwitchOn_Pin, GPIO_PIN_SET);
}

/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
void CPU_CACHE_Enable(void)
{
  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

/******************************************************************************/
/*   IRQ HANDLER TREATMENT Functions                                          */
/******************************************************************************/

/**
  * @brief  Function called from USARTx IRQ Handler when RXNE flag is set
  *         Function is in charge of reading character received on USART RX line.
  * @param  None
  * @retval None
  */
void USARTx_CharReception_Callback(void)
{
	__IO uint32_t received_char;

  /* Read Received character. RXNE flag is cleared by reading of RDR register */
  received_char = LL_USART_ReceiveData8(USARTx_INSTANCE);

  if(received_char == 0xF0  & msgnum == 0)
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

/**
  * @brief  Function called from USARTx IRQ Handler when RXNE flag is set
  *         Function is in charge of reading character received on USART RX line.
  * @param  None
  * @retval None
  */
void USARTy_CharReception_Callback(void)
{
	__IO uint32_t received_char;

  /* Read Received character. RXNE flag is cleared by reading of RDR register */
  received_char = LL_USART_ReceiveData8(USARTy_INSTANCE);

  /* Since this is the host port, there should never be any reception of data */
}

/**
  * @brief  Function called in case of error detected in USART IT Handler
  * @param  None
  * @retval None
  */
void Error_Callback(void)
{
	LL_USART_ClearFlag_FE(USARTx_INSTANCE);
	LL_USART_ClearFlag_FE(USARTy_INSTANCE);
	msgnum = 0;
}

void SendToUSART(uint8_t midichar)
{
	/* Send the packet thru host serial TX */
	LL_USART_TransmitData8(USARTy_INSTANCE, midichar);
	/* Wait for TXE flag to be raised */
	while (!LL_USART_IsActiveFlag_TXE(USARTy_INSTANCE))
	{
	}
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
