//************************ DSP Course Work Group 5 ********************************
// Author1: Qingyu Zhang; vn22984@bristol.ac.uk
// Author2: Shuran Yang; rw22242@bristol.ac.uk
// Author3: Ruilong Liu; hx22195@bristol.ac.uk
// Date: 08/02/2023
//*********************************************************************************

/*
 *  ======== gtz.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/sysbios/knl/Task.h>

#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "gtz.h"

#define DEBUG

// Compiler improvements
#define COMPILER_IMPROVE
// ========this three define cannot open at same time ========
// ========Longest
//#define ORIGIN
// ========Fastest
#define LOGIC_IMPROVE
// ========The instruction sets could not improve the efficiency
//#define INSTRUCTION_IMPROVE

void clk_SWI_Read_Data(UArg arg0);
void clk_SWI_GTZ_All_Freq(UArg arg0);

extern void task0_dtmfGen(void);
extern void task1_dtmfDetect(void);

extern int sample, tdiff, tdiff_final, gtz_out[8];
extern short coef[8];
extern int flag;

extern short dtmf_coef[DTMF_NUM];

short data[NO_OF_SAMPLES];
short *buffer;

/*
 *  ======== main ========
 */
int main() {
	System_printf("\nSystem Start\n");
	System_flush();

	/* Read binary data file */
	FILE* fp = fopen("../data.bin", "rb");
	if(fp==0) {
		System_printf("Error: Data file not found\n");
		System_flush();
		return 1;
	}
	fread(data, 2, NO_OF_SAMPLES, fp);
	buffer = (short*)malloc(2*8*10000);

	/* Create a Clock Instance */
	Clock_Params clkParams;

	/* Initialise Clock Instance with time period and timeout (system ticks) */
	Clock_Params_init(&clkParams);
	clkParams.period = 1;
	clkParams.startFlag = TRUE;

	/* Instantiate ISR for tone generation  */
	Clock_create(clk_SWI_Read_Data, TIMEOUT, &clkParams, NULL);

	/* Instantiate 8 parallel ISRs for each of the eight Goertzel coefficients */
	Clock_create(clk_SWI_GTZ_All_Freq, TIMEOUT, &clkParams, NULL);

	/* Start SYS_BIOS */
	BIOS_start();
}

/*
 *  ====== clk_SWI_Generate_DTMF =====
 *  Dual-Tone Generation
 *  ==================================
 */
void clk_SWI_Read_Data(UArg arg0) {
	static int tick;
	tick = Clock_getTicks();
	sample = data[tick%NO_OF_SAMPLES];
	sample =  _dshr(sample, 5);
}

/*
 *  ====== clk_SWI_GTZ =====
 *  gtz sweep
 *  ========================
 */
void clk_SWI_GTZ_All_Freq(UArg arg0) {
	// define variables for timing
	static int start, stop;

	// define feedback times as N
	static int N = 0;

	static int Goertzel_Value = 0;
	short input = (short) (sample);

	//The production during the calculation
   	static short delay[DTMF_NUM];
   	static short delay_1[DTMF_NUM] = {0};
   	static short delay_2[DTMF_NUM] = {0};

   	int i;
   	int prod1 = 0, prod2 = 0, prod3 = 0;

   	//Record start time
	start = Timestamp_get32();

	/* TODO 1. Complete the feedback loop of the GTZ algorithm*/
	/* ========================= */
#ifdef COMPILER_IMPROVE
#pragma MUST_ITERATE(256,,2);
#pragma UNROLL(4);
#endif

#ifdef ORIGIN
   	for(i = 0; i < DTMF_NUM; i++){
   		//dtmf_coef should >> 15 but * 2, we could let it >> 14
   		delay[i] = input + ((dtmf_coef[i] * delay_1[i]) >> 15) * 2 - delay_2[i];
		delay_2[i] = delay_1[i];
		delay_1[i] = delay[i];
   	}
	N++;
#endif

#ifdef LOGIC_IMPROVE
   	for(i = 0; i < DTMF_NUM; i++){
   		//dtmf_coef should >> 15 but * 2, we could let it >> 14
   		delay[i] = input + ((dtmf_coef[i] * delay_1[i]) >> 14) - delay_2[i];
		delay_2[i] = delay_1[i];
		delay_1[i] = delay[i];
   	}
	N++;
#endif

#ifdef INSTRUCTION_IMPROVE
	for(i = 0; i < DTMF_NUM; i++){
		//dtmf_coef should >> 15 but * 2, we could let it >> 14
		delay[i] = _dsub(_dadd(input, _dshr((_mpy32ll(dtmf_coef[i], delay_1[i])), 14)),delay_2[i]);
		delay_2[i] = delay_1[i];
		delay_1[i] = delay[i];
	}
	N = _dadd(N, 1);
#endif

	/* ========================= */
	//Record stop time
	stop = Timestamp_get32();
	//Record elapsed time
	tdiff = stop-start;

	if (N == N_VAL) {
	   	//Record start time
		start = Timestamp_get32();

		/* TODO 2. Complete the feedforward loop of the GTZ algorithm*/
		/* ========================= */
#ifdef COMPILER_IMPROVE
#pragma MUST_ITERATE(256,,2);
#pragma UNROLL(4);
#endif
		for(i = 0; i < DTMF_NUM; i++){

			//production of the Goertzel value
#ifdef ORIGIN
			prod1 = (int) (delay_1[i] * delay_1[i]) >> 8;
			prod2 = (int) (delay_2[i] * delay_2[i]) >> 8;
			prod3 = (int) ((((delay_1[i] * delay_2[i]) >> 8) * dtmf_coef[i]) >> 15) * 2;
			//get Goertzel value
			Goertzel_Value =  prod1 + prod2 - prod3;
#endif

#ifdef LOGIC_IMPROVE
			prod1 = (int) (delay_1[i] * delay_1[i]) >> 8;
			prod2 = (int) (delay_2[i] * delay_2[i]) >> 8;
			//dtmf_coef should >> 15 but * 2, we could let it >> 14
			prod3 = (int) (((delay_1[i] * delay_2[i]) >> 8) * dtmf_coef[i]) >> 14;
			//get Goertzel value
			Goertzel_Value =  prod1 + prod2 - prod3;
#endif

#ifdef INSTRUCTION_IMPROVE
			prod1 = (int) _dshr(_mpy32ll(delay_1[i], delay_1[i]), 8);
			prod2 = (int) _dshr(_mpy32ll(delay_2[i], delay_2[i]), 8);
			//dtmf_coef should >> 15 but * 2, we could let it >> 14
			prod3 = (int) _dshr(_mpy32ll(_dshr(_mpy32ll(delay_1[i],delay_2[i]), 8), dtmf_coef[i]), 14);
			//get Goertzel value
			Goertzel_Value =  _dsub(_dadd(prod1, prod2),prod3);
#endif

			//transfer results
			gtz_out[i] = Goertzel_Value;
			//init the delay value
			delay[i] = delay_1[i] = delay_2[i] = 0;
		}


		/* gtz_out[..] = ... */
		/* ========================= */
		flag = 1;
		N = 0;
//		memset(delay, 0, sizeof(delay));
//		memset(delay_1, 0, sizeof(delay_1));
//		memset(delay_2, 0, sizeof(delay_2));

		//Record stop time
		stop = Timestamp_get32();
		//Record elapsed time
		tdiff_final = stop-start;
	}
}
