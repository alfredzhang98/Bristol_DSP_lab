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
	System_printf("\n System Start\n");
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

   	//Record start time
	start = Timestamp_get32();

	static int Goertzel_Value = 0;
	short input = (short) (sample);

	//The production during the calculation
   	static short delay[DTMF_NUM];
   	static short delay_1[DTMF_NUM] = {0};
   	static short delay_2[DTMF_NUM] = {0};

   	int i;
   	int prod1, prod2, prod3;


	/* TODO 1. Complete the feedback loop of the GTZ algorithm*/
	/* ========================= */
   	for(i = 0; i < DTMF_NUM; i++){
   		prod1 = _dshr(((int) dtmf_coef[i] * (int) delay_1[i]), 15);
   		delay[i] = (short) input + _dshl(prod1, 1) - delay_2[i];
   		delay_2[i] = delay_1[i];
   		delay_1[i] = delay[i];
   	}


	/* ========================= */
	N++;

	//Record stop time
	stop = Timestamp_get32();
	//Record elapsed time
	tdiff += stop-start;

	if (N == N_VAL) {
	   	//Record start time
		start = Timestamp_get32();

		/* TODO 2. Complete the feedforward loop of the GTZ algorithm*/
		/* ========================= */
		for(i = 0; i < DTMF_NUM; i++){

			//production of the Goertzel value
			prod1 = _dshr(((int) delay_1[i] * delay_1[i]), 8);
			prod2 = _dshr(((int) delay_2[i] * delay_2[i]), 8);
			prod3 = _dshl(_dshr((_dshr((int) delay_1[i] * delay_2[i], 8) * dtmf_coef[i]), 15), 1);

			//get Goertzel value
			Goertzel_Value =  prod1 + prod2 - prod3;
			gtz_out[i] = Goertzel_Value;
			delay[i] = delay_1[i] = delay_2[i] = 0;
		}


		/* gtz_out[..] = ... */
		/* ========================= */
		flag = 1;
		N = 0;

		//Record stop time
		stop = Timestamp_get32();
		//Record elapsed time
		tdiff_final = stop-start;
	}
}
