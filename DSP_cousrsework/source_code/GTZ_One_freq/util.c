//************************ DSP Course Work Group 5 ********************************
// Author1: Qingyu Zhang; vn22984@bristol.ac.uk
// Author2: Shuran Yang; rw22242@bristol.ac.uk
// Author3: Ruilong Liu; hx22195@bristol.ac.uk
// Date: 08/02/2023
//*********************************************************************************

/*
 *  ======== util.c ========
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

UInt32 time1, time2;

char digit;

int freq1, freq2;
int mag1, mag2;
int flag = 0;

int sample, gtz_out[8];

short coef[8] = {0x6D02, 0x68AD, 0x63FC, 0x5EE7, 0x4A70, 0x4090, 0x3290, 0x23CE}; // Goertzel coefficients


void task0_dtmfGen(void)
{

// This task is used to read the symbol from the keyboard and set freq1 and freq2
	System_printf("\n I am in Task 0:\n");
	System_flush();
	Task_sleep(500); // to allow the GTZ to be calculated.

}

void task1_dtmfDetect(void)
{
//	int i, a1=0, a2=0, f1=0, f2=0, dig;


	System_printf("\n I am in Task 1 for the first time, please wait:\n");
	System_flush();

	while (1) {

		Task_sleep(210);  /* 0.25 second for 125us tick */
		if(flag != 0){
			System_printf("\n The GTZ is %d\n", gtz_out[0]);
			System_printf(" I am leaving Task 1, please wait for the next GTZ:\n");
			System_flush();
			flag = 0;
		}


//		a1=0, a2=0, f1=0, f2=0;
	 }

}

