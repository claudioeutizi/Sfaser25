clear;
close all;
clc;

%% Face90 WDF MXR Phase90

%% Import Input Audio Signal
[Vin,~] = audioread('jumpMono.wav');

%% LTSpice Files for Ground-Truth
filename = 'freqRespSpice.txt';
data = load(filename);
freq = data(:,1);
re = data(:,2);
im = data(:,3);
loglog(freq, abs(re+im*1i));
xlim([20 2*10^4]);
ylim([10^-3 3]);


%% Qui iniziano i problemi
