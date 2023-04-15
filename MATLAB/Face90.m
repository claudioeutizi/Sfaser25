clear;
close all;
clc;

%% Face90 WDF MXR Phase90

%% Import Input Audio Signal
[Vin,fs] = audioread('jumpMono.wav');
N=length(Vin);
%% Import reference LTspice frequency response
% ! before bjt stage ! 
% filename = 'freqRespSpice.txt';
% data = load(filename);
% freq = data(:,1);
% re = data(:,2);
% im = data(:,3);
% loglog(freq, abs(re+im*1i));
% xlim([20 2*10^4]);
% ylim([10^-3 3]);

data2=load('noBJT.txt');
freq2 = data2(:,1);
re2 = data2(:,2);
im2 = data2(:,3);
pre=abs(re2+im2*1i);

figure;
loglog(freq2,pre);
xlim([20 2*10^4]);
ylim([10^-3 3]);

data3=load('postBJT.txt');
re3 = data3(:,2);
im3 = data3(:,3);
post=abs(re3+im3*1i);

hold on;
loglog(freq2,post);
xlim([20 2*10^4]);
ylim([10^-3 3]);

figure;
d=post./pre;

semilogx(freq2,20*log10(d));
xlim([20 2*10^4]);


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
Idss=5.185*10^(-3);                                         %not sure, found experimentally
Rds = 1/(2*Idss*(LFO-Vref-Vcut)/Vcut^2);    %Not sure about the assumption of Vds=0


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

R2 = 150000;
R7 = 150000;
R8 = 150000;
R16 = 150000;

Qv = [   	  eye(11);
        -1 -1  0  0  0	0  0  0  0 0 0;
         0  0  1  0	 0  0  0  0	 0 0 0;
         0  0  1  1  1  1  1  1  1 1 1;
         0  0  0  0	 1  0  0  0  0 0 0;
         0  0  0  0	 0  0  1  0	 0 0 0;
         0  0  0  0	 0  0  0  0	 1 0 0;
        -1 -1 -1  0  0  0  0  0  0 0 0;
        -1 -1 -1  0  0  0  0  0  0 0 0;
        -1 -1 -1 -1	-1	0  0  0	 0 0 0;
        -1 -1 -1 -1	-1  0  0  0	 0 0 0;
        -1 -1 -1 -1	-1 -1 -1  0	 0 0 0;
        -1 -1 -1 -1 -1 -1 -1  0  0 0 0;
        -1 -1 -1 -1	-1 -1 -1 -1	-1 0 0;
        -1 -1 -1 -1 -1 -1 -1 -1 -1 0 0;];
    
Qi=[    eye(11);
    



]





