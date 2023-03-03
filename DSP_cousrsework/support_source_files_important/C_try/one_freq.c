/* Online C Compiler and Editor */
#include <stdio.h>
#include <math.h>

#define N 205 // length of input signal
#define Fs 8000 // sampling frequency
#define f0 697 // frequency of interest

int main()
{
    float signal[N]; // input signal
    float omega = 2.0 * M_PI * f0 / Fs; // normalized frequency
    float coeff = 2.0 * cos(omega); // filter coefficient
    float Q[N], Q1 = 0.0, Q2 = 0.0; // filter state variables
    float result; // output of the Goertzel filter
    int i;
    
    // generate input signal (sine wave at frequency f0)
    for (i = 0; i < N; i++) {
        signal[i] = 32,768 * sin(omega * i);
    }
    
    // run the Goertzel filter
    for (i = 0; i < N; i++) {
        Q[i] = coeff * Q1 - Q2 + signal[i];
        Q2 = Q1;
        Q1 = Q[i];
    }
    result = Q2*Q2 + Q1*Q1 - coeff * Q1 * Q2;
    
    // print the output
    printf("Output of Goertzel filter at frequency %d Hz: %f\n", f0, result);
    
    return 0;
}
