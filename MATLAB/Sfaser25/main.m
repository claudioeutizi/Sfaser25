clc;
clear;
close all;


input = 'audio';
if strcmp(input, 'sine')
f0 = 500;
fs = 192000;
Ts = 1/fs;
StopTime = 2*f0/f0;
t = 0:Ts:StopTime;
Vin = sin(2*pi*f0*t);
end

if strcmp(input, 'noise')
fs = 192000;
N=2*fs;
Ts = 1/fs;
t = 0:Ts:N*Ts-Ts;
Vin=randn(N,1);
end

if strcmp(input, 'audio')
[Vin,fs] = audioread('ExpSweep.wav');
Ts=1/fs;
% Vin=Vin(1:2*fs);
N=length(Vin);
t = 0:Ts:N*Ts-Ts;

[V_spiceOUT,fs2] = audioread('sweep.wav');
t_spiceOUT = 0:1/fs2:length(V_spiceOUT)/fs2-1/fs2;
end


stage0 = inputStage(Vin, Ts);
stage1 = shiftingStageLFO(stage0,Ts);
stage2 = shiftingStageLFO(stage1,Ts);
stage3 = shiftingStageLFO(stage2,Ts);
stage4 = shiftingStageLFO(stage3,Ts);

Vout = outputStage(stage0, stage4, Ts);

% loadedFile = load('stage0.txt');
% t_spice0 = loadedFile(:,1);
% V_spice0 = loadedFile(:,2);
% 
% 
% loadedFile = load('stage1.txt');
% t_spice1 = loadedFile(:,1);
% V_spice1 = loadedFile(:,2);
% 
% 
% loadedFile = load('stage4.txt');
% t_spice4 = loadedFile(:,1);
% V_spice4 = loadedFile(:,2);

% 
% loadedFile = load('output.txt');
% t_spiceOUT = loadedFile(:,1);
% V_spiceOUT = loadedFile(:,2);




% % stage0
% figure('color', 'white');
% plot(t, stage0, 'b', 'LineWidth', 2, 'DisplayName', 'WDF');
% hold on
% plot(t_spice0, V_spice0, 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');
% ylabel('\bf Voltage [V]','interpreter','latex','FontSize',13)
% xlabel('\bf Time [S]','interpreter','latex','FontSize',13)
% ax = gca;
% ax.FontSize = 13;
% l = legend('show','FontSize',15);
% set(l,'Interpreter','Latex');
% 
% % stage 1
% figure('color', 'white');
% plot(t, stage1, 'b', 'LineWidth', 2, 'DisplayName', 'WDF');
% hold on
% plot(t_spice1, V_spice1, 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');
% ylabel('\bf Voltage [V]','interpreter','latex','FontSize',13)
% xlabel('\bf Time [S]','interpreter','latex','FontSize',13)
% ax = gca;
% ax.FontSize = 13;
% l = legend('show','FontSize',15);
% set(l,'Interpreter','Latex');
% 
% % stage 4
% figure('color', 'white');
% plot(t, stage4, 'b', 'LineWidth', 2, 'DisplayName', 'WDF');
% hold on
% plot(t_spice4, V_spice4, 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');
% ylabel('\bf Voltage [V]','interpreter','latex','FontSize',13)
% xlabel('\bf Time [S]','interpreter','latex','FontSize',13)
% ax = gca;
% ax.FontSize = 13;
% l = legend('show','FontSize',15);
% set(l,'Interpreter','Latex');

% output

% figure('color', 'white');
% plot(t, Vout, 'b', 'LineWidth', 2, 'DisplayName', 'WDF');
% hold on
% plot(t_spiceOUT, V_spiceOUT, 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');
% ylabel('\bf Voltage [V]','interpreter','latex','FontSize',13)
% xlabel('\bf Time [S]','interpreter','latex','FontSize',13)
% ax = gca;
% ax.FontSize = 13;
% l = legend('show','FontSize',15);
% set(l,'Interpreter','Latex');
% figure;
% 
% plot(t_spiceOUT, (Vout(1:length(V_spiceOUT)) - V_spiceOUT))


figure;
Y = fft(Vin);
L = length(Vin);
P2 = abs(Y/L);
P1_in = P2(1:L/2+1);
P1_in(2:end-1) = 2*P1_in(2:end-1);
f = fs*(0:(L/2))/L;
loglog(f,20*log10(P1_in))
xlim([20, 20e3]);

figure;
Y = fft(Vout);
L = length(Vout);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f = fs*(0:(L/2))/L;
loglog(f,20*log10(P1))
xlim([20, 20e3]);



H=P1./P1_in;
figure;
loglog(f,medfilt1(20*log10(H),10));
xlim([20, 20e3]);


audiowrite('sweep2.wav',Vout,fs);

% window=2048;
% spectrogram(Vout, window, window/2, fs, 'yaxis', 'MinThreshold', -70);
% ylim([20*2/fs, 20e3*2/fs]);
% set(gca,'Yscale','log')


