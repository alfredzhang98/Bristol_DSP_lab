
#include <stdio.h>
#include <math.h>

#define N 206
#define Fs 8000 
#define f0 697 

int main()
{
    float signal[N]; 
    float omega = 2.0 * M_PI * f0 / Fs; 
    float coeff = 2.0 * cos(omega); 
    float delay[N], delay_1 = 0.0, delay_2 = 0.0;
    float result; 
    int i;

    for (i = 0; i < N; i++) {
        signal[i] = 32,768 * sin(omega * i);
    }
    
    for (i = 0; i < N; i++) {
        delay[i] = coeff * delay_1 - delay_2 + signal[i];
        delay_2 = delay_1;
        delay_1 = delay[i];
    }
    result = delay_2*delay_2 + delay_1*delay_1 - coeff*delay_1 * delay_2;
    
    printf("Output of Goertzel filter at frequency %d Hz: %f\n", f0, result);
    
    return 0;
}
