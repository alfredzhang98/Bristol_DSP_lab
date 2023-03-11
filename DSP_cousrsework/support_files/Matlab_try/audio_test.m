
clc
clear
close all;

[y1,Fs1]=audioread('answer.wav');
[y2,Fs2]=audioread('data_audio.wav');

subplot(2,1,1);
n1=length(y1);
amp=abs(fft(y1))/n1*2;
amp2=amp(1:n1/2);
f=Fs1/n1-1:Fs1/n1:Fs1/2-1; 

plot(f,amp2);
xlim([0 2000])
title('The frequency components of dectected answer wav file')
xlabel('Frquencies') 
ylabel('Magnitude') 
grid on


subplot(2,1,2);
n2=length(y2);
amp=abs(fft(y2))/n2*2;
amp2=amp(1:n2/2);
f=Fs1/n2-1:Fs1/n2:Fs1/2-1; 

plot(f,amp2);
xlim([0 2000])
title('The frequency components of real answer wav file')
xlabel('Frquencies') 
ylabel('Magnitude') 
grid on
