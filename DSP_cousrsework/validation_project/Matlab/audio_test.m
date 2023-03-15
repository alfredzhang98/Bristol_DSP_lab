
clc
clear
close all;

Tones = 8;

[y1,Fs1]=audioread('answer.wav');
[y2,Fs2]=audioread('data_audio.wav');


figure(1)
n1=length(y1);
amp_1=abs(fft(y1))/n1*2;
amp2_1=amp_1(1:n1/2);
f_1=Fs1/n1-1:Fs1/n1:Fs1/2-1; 

n2=length(y2);
amp_2=abs(fft(y2))/n2*2;
amp2_2=amp_2(1:n2/2);
f_2=Fs2/n2-1:Fs2/n2:Fs2/2-1; 

t1 = 1:1:n1;
subplot(2,2,1);
plot(t1,y1);
xlim([0 2000])
title('The detected answer wav file (8000 sample rate)')
xlabel('Time') 
ylabel('Magnitude') 
grid on

t2 = 1:1:n2;
subplot(2,2,2);
plot(t2,y2);
xlim([0 2000])
title('The real answer wav file (8000 sample rate)')
xlabel('Time') 
ylabel('Magnitude') 
grid on

subplot(2,2,3);
plot(f_1,amp2_1);
xlim([0 2000])
title('The frequency components of dectected answer wav file')
xlabel('Frquencies') 
ylabel('Magnitude') 
grid on

subplot(2,2,4);
plot(f_2,amp2_2);
xlim([0 2000])
title('The frequency components of real answer wav file')
xlabel('Frquencies') 
ylabel('Magnitude') 
grid on


figure(2)
n1=length(y1) / Tones;
f_1=Fs1/n1-1:Fs1/n1:Fs1/2-1; 

n2=length(y2) / Tones;
f_2=Fs2/n2-1:Fs2/n2:Fs2/2-1; 

for i = 1:Tones
    amp_1=abs(fft(y1(((i-1) * n1) + 1:i * n1,:)))/n1*2;
    amp2_1=amp_1(1:n1/2);
    subplot(8,2,i*2-1);
    [pks1,locs1] = findpeaks(amp2_1,"MinPeakHeight",0.1);
    plot(f_1,amp2_1,f_1(locs1),pks1,'or');
    hold on
    for j = 1:length(locs1)
        plot([f_1(locs1(j)),f_1(locs1(j))],[0,pks1(j)],'r--')
        text(f_1(locs1(j)) + 10 , 0.1,['<==' num2str(f_1(locs1(j)))])
    end
    xlim([0 2000])
    grid on
    if i == 1
        title('The frequency components of dectected answer wav file', ['sample rate = ', num2str(Fs1)])
    end
end

for i = 1:Tones
    amp_2=abs(fft(y2(((i-1) * n2) + 1:i * n2,:)))/n2*2;
    amp2_2=amp_2(1:n2/2);
    subplot(8,2,i*2);
    [pks2,locs2] = findpeaks(amp2_2,"MinPeakHeight",0.1);
    plot(f_2,amp2_2,f_2(locs2),pks2,'or');
    hold on
    for j = 1:length(locs2)
        plot([f_1(locs2(j)),f_1(locs2(j))],[0,pks2(j)],'r--')
        text(f_1(locs2(j)) + 10 , 0.1,['<==' num2str(f_2(locs2(j)))])
    end
    xlim([0 2000])
    grid on
    if i == 1
        title('The frequency components of real answer wav file', ['sample rate = ', num2str(Fs2)])
    end
end

grid off
hold off