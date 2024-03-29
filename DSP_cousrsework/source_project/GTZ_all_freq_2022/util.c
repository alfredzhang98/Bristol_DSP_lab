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

//#define _DEBUG

// there are tow function
#define READ_BIN
//#define READ_INPUT
// control the function to generate the wav file from the decoding the results
#define GENERATE_WAV
//define the way of detect and encode
#define WAY1
//#define WAY2

int tdiff,tdiff_final;

int *restrict sample, gtz_out[8];
int flag = 0;

// goertzel coefficients
short dtmf_coef[DTMF_NUM] = {0x6D02, 0x68AD, 0x63FC, 0x5EE7, 0x4A70, 0x4090, 0x3290, 0x23CE};
// goertzel freqs
short dtmf_freqs[DTMF_NUM] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};
//keys
char dtmf_keys[DTMF_HALF_NUM][DTMF_HALF_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

void task1_dtmfDetect();
void task2_dtmfGenerate(char* keys);
extern short* buffer;

extern void generateDTMF(int f1, int f2, float duration, int *sample);

void task1_dtmfDetect() {
	int i, j, n;

	int exist_row = 0;
	int exist_col = 0;
	char result[8];

#ifdef READ_BIN
	for(n=0;n<8;n++){
		while (!flag) Task_sleep(210);
		/* TODO 3. Complete code to detect the 8 digits based on the GTZ output */
		/* ========================= */
#ifdef _DEBUG
		printf("_______________________The %d tone _______________________\n", n);
#endif
		for(i = 0; i < DTMF_NUM; i++){
#ifdef _DEBUG
			printf("i: %d ; %d Hz: %d\n", i, dtmf_freqs[i], gtz_out[i]);
#endif

#ifdef WAY1
			for(j = 0; j < DTMF_HALF_NUM; j++){
				if(gtz_out[j] > gtz_out[exist_row])
				{
					exist_row = j;
				}
			}
			for(j = 0; j < DTMF_HALF_NUM; j++){
				if(gtz_out[j + DTMF_HALF_NUM] > gtz_out[exist_col + DTMF_HALF_NUM])
				{
					exist_col = j;
				}
			}
			result [n] = dtmf_keys[exist_row][exist_col];
#endif

// The  threshold should be change to fit the algorithm, so this way is limitation, please use way1
#ifdef WAY2
			for(j = 0; j < DTMF_HALF_NUM; j++){
				if(gtz_out[j] > THRESHOLD_POWER)
				{
					exist_row = j;
				}
			}
			for(j = 0; j < DTMF_HALF_NUM; j++){
				if(gtz_out[j + DTMF_HALF_NUM] > THRESHOLD_POWER)
				{
					exist_col = j;
				}
			}
			result [n] = dtmf_keys[exist_row][exist_col];
#endif
		}
			/* result[n] = ... */
		/* ========================= */
		printf("result[%d]: %c\n", n, result[n]);
		printf("Every feedback cycles tdiff: %d \t Final feedforward cycles tdiff_final: %d\n", tdiff, tdiff_final);
		printf("==================================================\n");
		//init the value
		flag = 0;
		tdiff = 0;
		tdiff_final = 0;
	}
	printf("\nDetection finished\n");
#endif

//read input and use the input to generate the wav
#ifdef READ_INPUT
	char input;
	printf("Please press the key (0 to 9, A, B, C, D, * and #) \n");
	n = 0;
	while(n < DTMF_NUM){
		scanf(" %c",&input);
		exist_row = 0xff;
		exist_col = 0xff;
		for (i = 0; i < DTMF_HALF_NUM; i++) {
			for (j = 0; j < DTMF_HALF_NUM; j++) {
				if(input == dtmf_keys[i][j]){
					exist_row = i;
					exist_col = j;
				}
			}
		}
		if(exist_row != 0xff && exist_col != 0xff){
			result [n] = dtmf_keys[exist_row][exist_col];
			printf("we get input to result[%d]: %c\n", n, result[n]);
			if(n < 7){
				printf("Great, Please press the next key, there are %d left \n", DTMF_NUM - n - 1);
			}else{
				printf("Well done, we get all the 8 numbers\n");
			}
			n++;
		}else{
			printf("Wrong, Please press the right key \n");
		}
	}

#endif

#ifdef GENERATE_WAV
	printf("Generating audio\n");
	task2_dtmfGenerate(result);
	printf("Finished\n");
#endif
}

void task2_dtmfGenerate(char* keys)
{
	//buffer 2*8*10000
	int fs = 8000;
	float tone_length = 0.5;
	int n_tones = 8;
	int samples_per_tone = (int) (tone_length * fs);
	int samples_total = samples_per_tone * n_tones;
	int i, n;
	double amp1, amp2;
#ifdef WAY2
	int j;
#endif
	int freq1 = 0,freq2 = 0;
	int temp_volume = 0;
	char digit;
	for(n = 0; n < n_tones; n++) {
		digit = keys[n];
		/* TODO 4. Complete the DTMF algorithm to generate audio signal based on the digits */
		/* ========================= */
#ifdef WAY1
		//Way1
		amp1 = 32768.0;
		if(digit == '1' || digit == '2' || digit == '3' || digit == 'A') freq1 = 697;
		else if(digit == '4' || digit == '5' || digit == '6' || digit == 'B') freq1 = 770;
		else if(digit == '7' || digit == '8' || digit == '9' || digit == 'C') freq1 = 852;
		else if(digit == '*' || digit == '0' || digit == '#' || digit == 'D') freq1 = 941;
		else{
			freq1 = 0;
			amp1 = 0.0;
		}

		amp2 = 32768.0;
		if(digit == '1' || digit == '4' || digit == '7' || digit == '*') freq2 = 1209;
		else if(digit == '2' || digit == '5' || digit == '8' || digit == '0') freq2 = 1336;
		else if(digit == '3' || digit == '6' || digit == '9' || digit == '#') freq2 = 1477;
		else if(digit == 'A' || digit == 'B' || digit == 'C' || digit == 'D') freq2 = 1633;
		else{
			freq2 = 0;
			amp2 = 0.0;
		}

		for(i = 0; i < samples_per_tone; i++){
			temp_volume =  (int) ((amp1 * sin(2.0 * PI * freq1 * i / fs) +  amp2 * sin(2.0 * PI *freq2 * i / fs)) / 2);
//			*(buffer + n * samples_per_tone + i) = (short) temp_volume;
			buffer[n * samples_per_tone + i] = (short) temp_volume;
		}

#endif

#ifdef WAY2
		//Way2
		for (i = 0; i < DTMF_HALF_NUM; i++) {
			for (j = 0; j < DTMF_HALF_NUM; j++) {
				if(digit == dtmf_keys[i][j]){
					freq1 = dtmf_freqs[i];
					freq2 = dtmf_freqs[j + DTMF_HALF_NUM];
				}
			}
		}
		for(i = 0; i < samples_per_tone; i++){
			temp_volume =  (int) ((32768.0 * sin(2.0 * PI * freq1 * i / fs) +  32768.0 * sin(2.0 * PI *freq2 * i / fs)) / 2);
//			*(buffer + n * samples_per_tone + i) = (short) temp_volume;
			buffer[n * samples_per_tone + i] = (short) temp_volume;
		}

#endif


		/* buffer[..] = ... */
		/* ========================= */
	}

	/* Writing the data to a wav file */
	FILE* fp = fopen("../answer.wav", "wb");
	int datasize = samples_total*2;
	int filesize = 36+datasize;
	int headersize = 16;
	int datatype = 1;
	int nchannel = 1;
	int byterate = fs*2;
	int align = 2;
	int bitpersample = 16;

	fwrite("RIFF", 1, 4, fp);
	fwrite(&filesize, 4, 1, fp);
	fwrite("WAVE", 1, 4, fp);
	fwrite("fmt ", 1, 4, fp);
	fwrite(&headersize, 4, 1, fp);
	fwrite(&datatype, 2, 1, fp);
	fwrite(&nchannel, 2, 1, fp);
	fwrite(&fs, 4, 1, fp);
	fwrite(&byterate, 4, 1, fp);
	fwrite(&align, 2, 1, fp);
	fwrite(&bitpersample, 2, 1, fp);
	fwrite("data", 1, 4, fp);
	fwrite(&datasize, 4, 1, fp);
	fwrite(buffer, 2, samples_total, fp);
	fclose(fp);
}
