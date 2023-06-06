close all;
clear;
clc;
%%44
[Vin,fs] = audioread('Sine0.35.wav');
[Vout,fs] = audioread('SineSpiceNorm44.wav');


Vin=Vin(:,1);
Vout=-Vout(:,1)*1.3;


Y = fft(Vin);
L = length(Vin);
P2 = abs(Y/L);
P1_in = P2(1:L/2+1);
P1_in(2:end-1) = 2*P1_in(2:end-1);
f = fs*(0:(L/2))/L;
% loglog(f,20*log10(P1_in))
% xlim([20, 20e3]);


Y = fft(Vout);
L = length(Vout);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f1 = fs*(0:(L/2))/L;
% loglog(f1,20*log10(P1))
% xlim([20, 20e3]);


% H=P1./P1_in;
% figure;
% loglog(f,medfilt1(20*log10(H),5));
% xlim([20, 20e3]);

t = 0:1/fs:(L-1)/fs;




figure('color', 'white');
%plot(Vin);
%hold on; 
plot(t(fs:end), Vin(fs:end), 'b', 'LineWidth', 2, 'DisplayName', 'WDF');

hold on
%figure('color', 'white');
aligned=circshift(Vout/1.2,8344);
plot(t(fs:end),aligned(fs:end) , 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');

ylabel('\bf Voltage [V]','interpreter','latex','FontSize',13)
xlabel('\bf Time [S]','interpreter','latex','FontSize',13)
ax = gca;
ax.FontSize = 13;
l = legend('show','FontSize',15);
set(l,'Interpreter','Latex');
figure;
error= Vin(fs:end)-aligned(fs:end);
E=sum(error.^2)/L
plot(t(fs:end), error);

figure('color', 'white');
%plot(Vin);
%hold on; 
loglog(f, 20*log10(P1_in), 'b', 'LineWidth', 2, 'DisplayName', 'WDF');
xlim([20, 20e3]);
ylim([-120, -25]);
hold on
%figure('color', 'white');
loglog(f1, 20*log10(P1), 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');
xlim([20, 20e3]);
ylim([-120, -25]);
ylabel('\bf Voltage [V]','interpreter','latex','FontSize',13)
xlabel('\bf Time [S]','interpreter','latex','FontSize',13)
ax = gca;
ax.FontSize = 13;
l = legend('show','FontSize',15);
set(l,'Interpreter','Latex');



% figure;
% window=2048;
% spectrogram(Vout, window, window/2, fs, 'yaxis', 'MinThreshold', -70);
% ylim([20*2/fs, 20e3*2/fs]);
% set(gca,'Yscale','log')
% 
% figure;
% window=2048;
% spectrogram(Vin, window, window/2, fs, 'yaxis', 'MinThreshold', -70);
% ylim([20*2/fs, 20e3*2/fs]);
% set(gca,'Yscale','log')
