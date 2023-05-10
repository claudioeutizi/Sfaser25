clear;
close all;


[Vin,fs] = audioread('real90.wav');
Ts=1/fs;
Vin=(Vin(:,1)+Vin(:,2))/2;
Vin=Vin(fs:15*fs);
N=length(Vin);
t = 0:Ts:N*Ts-Ts;

window=2048;

spectrogram(Vin, window, window/2,fs, 'yaxis', 'MinThreshold', -50);
ylim([20*2/fs, 20e3*2/fs]);
set(gca,'Yscale','log')

[Vin,fs] = audioread('TestPlugin.wav');
Ts=1/fs;
Vin=(Vin(:,1)+Vin(:,2))/2;
Vin=Vin(fs:6*fs);
N=length(Vin);
t = 0:Ts:N*Ts-Ts;

window=2048;

figure;
spectrogram(Vin, window, window/2,fs, 'yaxis', 'MinThreshold', -50);
ylim([20*2/fs, 20e3*2/fs]);
set(gca,'Yscale','log')