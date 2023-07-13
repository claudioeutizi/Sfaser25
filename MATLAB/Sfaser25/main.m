clc;
clear;
close all;


input = 'sine';

if strcmp(input, 'sine')
f0 = 1000;
fs = 96000;
Ts = 1/fs;
StopTime = 1;
t = 0:Ts:StopTime;
Vin = sin(2*pi*f0*t);
% Vin=Vin(1:end-1);
end

if strcmp(input, 'noise')
fs = 192000;
N=0.5*fs;
Ts = 1/fs;
t = 0:Ts:N*Ts-Ts;
Vin=randn(N,1);
end

if strcmp(input, 'audio')
[Vin,fs] = audioread('sine.wav');
Ts=1/fs;
% Vin=Vin(1:2*fs);
N=length(Vin);
t = 0:Ts:N*Ts-Ts;

end


stage0 = inputStage(Vin, Ts);
stage1 = shiftingStageLFO(stage0,Ts);
stage2 = shiftingStageLFO(stage1,Ts);
stage3 = shiftingStageLFO(stage2,Ts);
stage4 = shiftingStageLFO(stage3,Ts);

Vout = outputStage(stage0, stage4, Ts);

% figure;
% Y = fft(Vin);
% L = length(Vin);
% P2 = abs(Y/L);
% P1_in = P2(1:L/2+1);
% P1_in(2:end-1) = 2*P1_in(2:end-1);
% f = fs*(0:(L/2))/L;
% loglog(f,20*log10(P1_in))
% xlim([20, 20e3]);
% 
% figure;
% Y = fft(Vout);
% L = length(Vout);
% P2 = abs(Y/L);
% P1 = P2(1:L/2+1);
% P1(2:end-1) = 2*P1(2:end-1);
% f = fs*(0:(L/2))/L;
% loglog(f,20*log10(P1))
% xlim([20, 20e3]);
% 
% 
% 
% H=P1./P1_in.';
% figure;
% loglog(f,medfilt1(20*log10(H),5));
% xlim([20, 20e3]);


audiowrite('output.wav',Vout,fs);

window=2048;
spectrogram(Vout, window, window/2, fs, 'yaxis', 'MinThreshold', -70);
ylim([20*2/fs, 20e3*2/fs]);
set(gca,'Yscale','log')



