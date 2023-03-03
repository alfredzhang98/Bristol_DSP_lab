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

#define DEBUG

int tdiff,tdiff_final;

int sample, gtz_out[8];
int flag = 0;

short freqs_results[8];

// goertzel freqs
short dtmf_freqs[DTMF_NUM] = {697, 770, 852, 941, 1209, 1336, 1477, 1633};

// goertzel coefficients
short dtmf_coef[DTMF_NUM] = {0x6D02, 0x68AD, 0x63FC, 0x5EE7, 0x4A70, 0x4090, 0x3290, 0x23CE};
// key pad
char dtmf_keys[DTMF_HALF_NUM][DTMF_HALF_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// digit freqs
short digit_freqs[DIGHIT_NUM][2] = {
    {697, 1209}, // 1
    {697, 1336}, // 2
    {697, 1477}, // 3
    {697, 1633}, // A
    {770, 1209}, // 4
    {770, 1336}, // 5
    {770, 1477}, // 6
    {770, 1633}, // B
    {852, 1209}, // 7
    {852, 1336}, // 8
    {852, 1477}, // 9
    {852, 1633}, // C
    {941, 1209}, // *
    {941, 1336}, // 0
    {941, 1209}, // #
    {941, 1633}  // D
};

void task1_dtmfDetect();
void task2_dtmfGenerate(char* keys);
extern short* buffer;

void task1_dtmfDetect() {
	int i, j, n;
	char result[8];

	for(n=0;n<8;n++) {
		while (!flag) Task_sleep(300);
		/* TODO 3. Complete code to detect the 8 digits based on the GTZ output */
		/* ========================= */
		j = 0;
		for(i = 0; i < DTMF_NUM; i++){
			printf("%d Hz: %d\n", dtmf_freqs[i], gtz_out[i]);
//			if(gtz_out[i] > THRESHOLD_POWER){
//				freqs_results[j] = dtmf_freqs[i];
//				j++;
//			}
//			if(j == 2){
//#ifdef DEBUG
//				printf("we get 2 freqs\n");
//#endif
//			}else{
//#ifdef DEBUG
//				printf("we get too more freqs, cannot be decode\n");
//#endif
//			}
		}

		/* result[n] = ... */
		/* ========================= */
		printf("%c\n", result[n]);
		flag = 0;
	}
	printf("\nDetection finished\n");
	printf("Generating audio\n");
	task2_dtmfGenerate(result);
	printf("Finished\n");
}

void task2_dtmfGenerate(char* keys)
{
	int fs = 10000;
	float tone_length = 0.5;
	int n_tones = 8;
	int samples_per_tone = (int) (tone_length * fs);
	int samples_total = samples_per_tone * n_tones;
	int i, n;
	char digit;
	for(n=0;n<n_tones;n++) {
		digit = keys[n];
		/* TODO 4. Complete the DTMF algorithm to generate audio signal based on the digits */
		/* ========================= */

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