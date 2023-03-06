clc
clear
close all;

% from the python generate
coef = 0.817779541015625;
PI = 3.1415926535897932384626433832795;
SAMPLE_RATE = 8000;
AMP = 32768;

delay=0;
delay_1=0;
delay_2=0;

t=0;

powers = zeros(1,2000);

for freq=1:2000
    t=0;
    for i = 0:206
        input = AMP * sin(2.0*PI*freq * t / SAMPLE_RATE);
        t = t+1;
        delay=2*coef*delay_1 + input - delay_2;
        delay_2 = delay_1;
        delay_1 = delay;
    end
    power = delay_1^2 + delay_2^2 - 2*delay_1*delay_2*coef;
    powers(1,freq)=power;
end

stem(powers)





