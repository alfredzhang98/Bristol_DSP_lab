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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "gtz.h"

#define NUM 0

void clk_SWI_Generate_DTMF(UArg arg0);
void clk_SWI_GTZ_0697Hz(UArg arg0);

extern void task0_dtmfGen(void);
extern void task1_dtmfDetect(void);

extern float calculate_coef(int freq);

extern char digit;
extern int sample, mag1, mag2, freq1, freq2, gtz_out[8];
extern int flag;
extern short coef[8];
extern short freqs[8];

// The Goertzel parameter
int N = 0;
const int N_const = 206;


/*
 *  ======== main ========
 */
void main(void)
{
	System_printf("\n I am in main :\n");
	System_flush();
	/* Create a Clock Instance */
    Clock_Params clkParams;

    /* Initialise Clock Instance with time period and timeout (system ticks) */
    Clock_Params_init(&clkParams);
    clkParams.period = 1;
    clkParams.startFlag = TRUE;

    /* Instantiate ISR for tone generation  */
	Clock_create(clk_SWI_Generate_DTMF, TIMEOUT, &clkParams, NULL);

    /* Instantiate 8 parallel ISRs for each of the eight Goertzel coefficients */
	Clock_create(clk_SWI_GTZ_0697Hz, TIMEOUT, &clkParams, NULL);

	mag1 = 32768.0; mag2 = 32768.0; freq1 = freqs[NUM]; // I am setting freq1 = 770Hz to test my GTZ algorithm with one frequency.

	/* Start SYS_BIOS */
    BIOS_start();
}

/*
 *  ====== clk0Fxn =====
 *  Dual-Tone Generation
 *  ====================
 */
void clk_SWI_Generate_DTMF(UArg arg0)
{
	static int tick;
	tick = Clock_getTicks();
//	sample = (int) 32768.0*sin(2.0*PI*freq1*TICK_PERIOD*tick) + 32768.0*sin(2.0*PI*freq2*TICK_PERIOD*tick);
	sample = (int) mag1*sin(2.0*PI*freq1*TICK_PERIOD*tick) + 32768.0*sin(2.0*PI*0*TICK_PERIOD*tick);
	sample = sample >> 12;

}

/*
 *  ====== clk_SWI_GTZ =====
 *  gtz sweep
 *  ====================
 */
void clk_SWI_GTZ_0697Hz(UArg arg0)
{
	int prod1, prod2, prod3;
	short input;
   	static short delay;
   	static short delay_1 = 0;
   	static short delay_2 = 0;

   	static int Goertzel_Value = 0;
   	short coef_1 = coef[NUM];


   	//we have several intermediates which need recursion
	input = (short) sample;

	delay = input + ((coef_1 * delay_1) >> 14) - delay_2;
	delay_2 = delay_1;
	delay_1 = delay;
	N++;
	//every 205 times get one result
	if(N == N_const){
		//production of the Goertzel value
		prod1 = (int) (delay_1 * delay_1);
		prod2 = (int) (delay_2 * delay_2);
		prod3 = (int) delay_1 * ((delay_2 * coef_1) >> 14);
		//get Goertzel value
		//ignore the int in the low bin position
		Goertzel_Value =  (prod1 + prod2 - prod3) >> 15;
		//scale up the value to get the same value of each test
		Goertzel_Value <<= 8;
		//transfer results
		gtz_out[0] = Goertzel_Value;
		//Init the calculation
		N=0;
		flag = 1;
		delay = delay_1 = delay_2 = 0;
	}
}

// calculation the coefficient of a particular frequency.
float calculate_coef(int freq){
	int n_1 = N_const;
	int K = round(0.5 + n_1 * freq / SAMPLING_RATE);
	float W = (K * 2 * PI / n_1);
	float cos_w = cos(W);
	float coef = 2 * cos_w;
	return coef;
}






