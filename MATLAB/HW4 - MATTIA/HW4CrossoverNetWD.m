clear all
close all
clc

% Name: Mattia Massimi                     
% Student ID: 102635   


%% Import Input Audio Signal
[Vin,~] = audioread('ExpSweep.wav');

%% LTSpice Files for Ground-Truth
[OutLowSpice,~]=audioread('outlowsweep.wav');
[OutMidSpice,~]=audioread('outmidsweep.wav');
[OutHighSpice,FsLTSpice]=audioread('outhighsweep.wav');
TsLTSpice=1/FsLTSpice;

%% Sampling frequency (to be varied: FsLTSpice/downSampFact, with downSampFact={4,3,2})
downSampFact=2;
Fs =FsLTSpice/downSampFact; 

%% Downsample Input Signal
Vin=Vin([1:downSampFact:end]);

%% Sampling Period
Ts=1/Fs;
%% Number of Samples
Nsamp=length(Vin);
%% Simulated time
tstop=Nsamp*Ts;
%% Parameters of Dynamic Element
L1=0.35*10^(-3);
L2=0.35*10^(-3);
L3=3.5*10^(-3);
L4=3.5*10^(-3);
C1= 2.8*10^(-6);
C2= 2.8*10^(-6);
C3= 28*10^(-6);
C4= 4.7*10^(-6);
C5=28*10^(-6);
C6=47*10^(-6);
%% Resistive Parameters
R1=10;
RspkLow=8;
R2=10;
RspkMid=8;
RspkHigh=8;
%% WDF setting of free parameters (adaptation conditions)
%highs
z2H=Ts/(2*C1);
z5H=2*L1/Ts;
z6H=RspkHigh;
z4H=(z6H*z5H)/(z6H+z5H);
z3H=z4H;
z1H=z3H+z2H;

%mids
z18M=Ts/(2*C4);
z17M=R1;
z16M=z18M+z17M;
z14M=RspkMid;
z15M=z16M;
z13M=(z14M*z15M)/(z14M+z15M);
z12M=z13M;
z11M=2*L3/Ts;
z10M=(z11M*z12M)/(z11M+z12M);
z9M=z10M;
z8M=Ts/(2*C3);
z7M=z8M+z9M;
z6M=z7M;
z5M=Ts/(2*C2);
z4M=(z5M*z6M)/(z5M+z6M);
z3M=z4M;
z2M=2*L2/Ts;
z1M=z2M+z3M;

%lows
z12L=Ts/(2*C6);
z11L=R2;
z10L=z11L+z12L;
z9L=z10L;
z8L=RspkLow;
z7L=(z8L*z9L)/(z8L+z9L);
z6L=z7L;
z5L=Ts/(2*C5);
z4L=(z5L*z6L)/(z5L+z6L);
z3L=z4L;
z2L=2*L4/Ts;
z1L=z2L+z3L;


%% Computation of Scattering Matrices
%{%}
Bser = [1,1,1];
Qpar = [1,1,1];

%high
Z_H1= diag([z1H,z2H,z3H]);
Z_H2= diag([z4H,z5H,z6H]);

S_H1= eye(3) - 2*Z_H1*Bser'*inv(Bser*Z_H1*Bser')*Bser;
S_H2= 2*Qpar'*inv(Qpar*inv(Z_H2)*Qpar')*Qpar*inv(Z_H2) - eye(3);

%mid
Z_M1= diag([z1M,z2M,z3M]);
Z_M2= diag([z4M,z5M,z6M]);
Z_M3= diag([z7M,z8M,z9M]);
Z_M4= diag([z10M,z11M,z12M]);
Z_M5= diag([z13M,z14M,z15M]);
Z_M6= diag([z16M,z17M,z18M]);

S_M1=eye(3) - 2*Z_M1*Bser'*inv(Bser*Z_M1*Bser')*Bser;
S_M2=2*Qpar'*inv(Qpar*inv(Z_M2)*Qpar')*Qpar*inv(Z_M2) - eye(3);
S_M3=eye(3) - 2*Z_M3*Bser'*inv(Bser*Z_M3*Bser')*Bser;
S_M4=2*Qpar'*inv(Qpar*inv(Z_M4)*Qpar')*Qpar*inv(Z_M4) - eye(3);
S_M5=2*Qpar'*inv(Qpar*inv(Z_M5)*Qpar')*Qpar*inv(Z_M5) - eye(3);
S_M6=eye(3) - 2*Z_M6*Bser'*inv(Bser*Z_M6*Bser')*Bser;

%low
Z_L1=diag([z1L,z2L,z3L]);
Z_L2=diag([z4L,z5L,z6L]);
Z_L3=diag([z7L,z8L,z9L]);
Z_L4=diag([z10L,z11L,z12L]);

S_L1=eye(3) - 2*Z_L1*Bser'*inv(Bser*Z_L1*Bser')*Bser;
S_L2=2*Qpar'*inv(Qpar*inv(Z_L2)*Qpar')*Qpar*inv(Z_L2) - eye(3);
S_L3=2*Qpar'*inv(Qpar*inv(Z_L3)*Qpar')*Qpar*inv(Z_L3) - eye(3);
S_L4=eye(3) - 2*Z_L4*Bser'*inv(Bser*Z_L4*Bser')*Bser;


%% Initialization of Waves
b2H=0;
b5H=0;
a6H=0;

b2M=0;
b5M=0;
b8M=0;
b11M=0;
a14M=0;
a17M=0;
b18M=0;

b2L=0;
b5L=0;
a8L=0;
a11L=0;
b12L=0;

%% Initialize Output Signals
% Low
VoutLow=zeros(size(Vin));
% Mid
VoutMid=zeros(size(Vin));
% High
VoutHigh=zeros(size(Vin));

ii=0;
while (ii<Nsamp)
    ii=ii+1;

    %% Manage Dynamic Elements
     a2H=b2H;
     a5H=-b5H;
     
     a2M=-b2M;
     a5M=b5M;
     a8M=b8M;
     a11M=-b11M;
     a18M=b18M;
     
     a2L=-b2L;
     a5L=b5L;
     a12L=b12L;
    
    %% Forward Scan
    b4H=S_H2(1,:)*[0; a5H; a6H];
    a3H=b4H;
    b1H=S_H1(1,:)*[0; a2H; a3H];
    
    b16M=S_M6(1,:)*[0; a17M; a18M];
    a15M=b16M;
    b13M=S_M5(1,:)*[0; a14M; a15M];
    a12M=b13M;
    b10M=S_M4(1,:)*[0; a11M; a12M];
    a9M=b10M;
    b7M=S_M3(1,:)*[0; a8M; a9M];
    a6M=b7M;
    b4M=S_M2(1,:)*[0; a5M; a6M];
    a3M=b4M;
    b1M=S_M1(1,:)*[0; a2M; a3M];
    
    b10L=S_L4(1,:)*[0; a11L; a12L];
    a9L=b10L;
    b7L=S_L3(1,:)*[0; a8L; a9L];
    a6L=b7L;
    b4L=S_L2(1,:)*[0; a5L; a6L];
    a3L=b4L;
    b1L=S_L1(1,:)*[0; a2L; a3L];
   
    %% Local Root Scattering
    a1H=2*Vin(ii)-b1H;
    a1M=2*Vin(ii)-b1M;
    a1L=2*Vin(ii)-b1L;
    %% Backward Scan
    b3H=S_H1(3,:)*[a1H; a2H; a3H];
    b2H=S_H1(2,:)*[a1H; a2H; a3H];
    a4H=b3H;
    b6H=S_H2(3,:)*[a4H; a5H; a6H];
    b5H=S_H2(2,:)*[a4H; a5H; a6H];
    
    b3M=S_M1(3,:)*[a1M; a2M; a3M];
    b2M=S_M1(2,:)*[a1M; a2M; a3M];
    a4M=b3M;
    b6M=S_M2(3,:)*[a4M; a5M; a6M];
    b5M=S_M2(2,:)*[a4M; a5M; a6M];
    a7M=b6M;
    b9M=S_M3(3,:)*[a7M; a8M; a9M];
    b8M=S_M3(2,:)*[a7M; a8M; a9M];
    a10M=b9M;
    b12M=S_M4(3,:)*[a10M; a11M; a12M];
    b11M=S_M4(2,:)*[a10M; a11M; a12M];
    a13M=b12M;
    b15M=S_M5(3,:)*[a13M; a14M; a15M];
    b14M=S_M5(2,:)*[a13M; a14M; a15M];
    a16M=b15M;
    b18M=S_M6(3,:)*[a16M; a17M; a18M];
    b17M=S_M6(2,:)*[a16M; a17M; a18M];
    
    b3L=S_L1(3,:)*[a1L; a2L; a3L];
    b2L=S_L1(2,:)*[a1L; a2L; a3L];
    a4L=b3L;
    b6L=S_L2(3,:)*[a4L; a5L; a6L];
    b5L=S_L2(2,:)*[a4L; a5L; a6L];
    a7L=b6L;
    b9L=S_L3(3,:)*[a7L; a8L; a9L];
    b8L=S_L3(2,:)*[a7L; a8L; a9L];
    a10L=b9L;
    b12L=S_L4(3,:)*[a10L; a11L; a12L];
    b11L=S_L4(2,:)*[a10L; a11L; a12L];
    
    %% Read Output
    VoutHigh(ii)=-(a6H+b6H)/2;
    VoutMid(ii)=(a14M+b14M)/2;
    VoutLow(ii)=-(a8L+b8L)/2;
end


%% Output Plots
figure
set(gcf, 'Color', 'w');
subplot(311)
plot(TsLTSpice*[1:length(OutLowSpice)],OutLowSpice,'r','Linewidth',2); hold on;
plot(Ts*[1:Nsamp],VoutLow,'b--','Linewidth',1); grid on; xlim([0,tstop]); 
xlabel('time [seconds]','Fontsize',16,'interpreter','latex');
ylabel('$V_{\mathrm{outLow}}$ [V]','Fontsize',16,'interpreter','latex');
legend('LTspice','WDF','Fontsize',16,'interpreter','latex');
title('Output Signals','Fontsize',18,'interpreter','latex');
subplot(312)
plot(TsLTSpice*[1:length(OutMidSpice)],OutMidSpice,'r','Linewidth',2); hold on;
plot(Ts*[1:Nsamp],VoutMid,'b--','Linewidth',1); grid on; xlim([0,tstop]);
xlabel('time [seconds]','Fontsize',16,'interpreter','latex');
ylabel('$V_{\mathrm{outMid}}$ [V]','Fontsize',16,'interpreter','latex');
subplot(313)
plot(TsLTSpice*[1:length(OutHighSpice)],OutHighSpice,'r','Linewidth',2); hold on;
plot(Ts*[1:Nsamp],VoutHigh,'b--','Linewidth',1); grid on; xlim([0,tstop]);
xlabel('time [seconds]','Fontsize',16,'interpreter','latex');
ylabel('$V_{\mathrm{outHigh}}$ [V]','Fontsize',16,'interpreter','latex');

%% Error Plots
figure
set(gcf, 'Color', 'w');
subplot(311)
plot(Ts*[1:Nsamp],OutLowSpice([1:downSampFact:end])-VoutLow,'k','Linewidth',1);grid on; xlim([0,tstop]);
xlabel('time [seconds]','Fontsize',16,'interpreter','latex');
ylabel('$E_{\mathrm{outLow}}$ [V]','Fontsize',16,'interpreter','latex');
title(['Error Signals. $F_{\mathrm{s}}=$ ',num2str(Fs),' Hz'],'Fontsize',18,'interpreter','latex');
subplot(312)
plot(Ts*[1:Nsamp],OutMidSpice([1:downSampFact:end])-VoutMid,'k','Linewidth',1);grid on; xlim([0,tstop]);
xlabel('time [seconds]','Fontsize',16,'interpreter','latex');
ylabel('$E_{\mathrm{outMid}}$ [V]','Fontsize',16,'interpreter','latex');
subplot(313)
plot(Ts*[1:Nsamp],OutHighSpice([1:downSampFact:end])-VoutHigh,'k','Linewidth',1);grid on; xlim([0,tstop]);
xlabel('time [seconds]','Fontsize',16,'interpreter','latex');
ylabel('$E_{\mathrm{outHigh}}$ [V]','Fontsize',16,'interpreter','latex');

