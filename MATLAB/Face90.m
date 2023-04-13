clear;
close all;
clc;

%% Face90 WDF MXR Phase90

%% Import Input Audio Signal
[Vin,fs] = audioread('jumpMono.wav');
N=length(Vin);
%% Import reference LTspice frequency response
% ! before bjt stage ! 
filename = 'freqRespSpice.txt';
data = load(filename);
freq = data(:,1);
re = data(:,2);
im = data(:,3);
loglog(freq, abs(re+im*1i));
xlim([20 2*10^4]);
ylim([10^-3 3]);


%% Parameters of dynamic elements
C1 = 47*10^(-9);
C2 = 47*10^(-9);
C3 = 47*10^(-9);
C5 = 0.01*10^(-6);
C6 = 47*10^(-9);
C9 = 47*10^(-9);




%% Resistive elements

%JFETs params
Vcut = -2.021;                                      %in this particular JFET used in LTspice
Vref = 5.1;
LFO=3.8;
Idss=5.185;                                         %not sure, found experimentally
Rds = 1/(2*Idss*10^(-3)*(LFO-Vref-Vcut)/Vcut^2);    %Not sure about the assumption of Vds=0


R14 = 470000;

R1 = 10000;
R3 = 10000;
R5 = 10000;
R10 = 10000;
R11 = 10000;
R12 = 10000;
R13 = 10000;
R17 = 10000;
R18 = 10000;

R6 = 24000;
R23 = 24000;
R25 = 24000;
R26 = 24000;

R2=R7=R8=R16=150000;



