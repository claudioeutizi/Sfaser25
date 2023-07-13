close all;
clear;
clc;

[Vin,fs] = audioread('sineNewImp96.wav');
[Vout,fs] = audioread('SineSpiceNorm.wav');


Vin=Vin(:,1);

Vout=-Vout(:,1)*1.2;


Y = fft(Vin);
L = length(Vin);
P2 = abs(Y/L);
P1_in = P2(1:L/2+1);
P1_in(2:end-1) = 2*P1_in(2:end-1);
f = fs*(0:(L/2))/L;



Y = fft(Vout);
L = length(Vout);
P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);
f1 = fs*(0:(L/2))/L;


t = 0:1/fs:(L-1)/fs;



if 1
figure('color', 'white');
plot(t(fs:end), Vin(fs:end), 'b', 'LineWidth', 2, 'DisplayName', 'WDF');

hold on
%for 96k is -28622
%fot 44k is 18163
aligned=circshift(Vout/1.2,-28622);
plot(t(fs:end),aligned(fs:end) , 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');

ylabel('\bf Amplitude[dB]','interpreter','latex','FontSize',13)
xlabel('\bf Frequency[Hz]','interpreter','latex','FontSize',13)
ax = gca;
ax.FontSize = 13;
l = legend('show','FontSize',15);
set(l,'Interpreter','Latex');
figure;
error= Vin(fs:end)-aligned(fs:end);
Et=sum(error.^2)/L;
plot(t(fs:end), error);

figure('color', 'white');
loglog(f, 20*log10(P1_in), 'b', 'LineWidth', 2, 'DisplayName', 'WDF');
xlim([20, 20e3]);
ylim([-120, -25]);
hold on
loglog(f1, 20*log10(P1), 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');
xlim([20, 20e3]);
ylim([-120, -25]);
ylabel('\bf Amplitude[dB]','interpreter','latex','FontSize',13)
xlabel('\bf Frequency[Hz]','interpreter','latex','FontSize',13)
ax = gca;
ax.FontSize = 13;
l = legend('show','FontSize',15);
set(l,'Interpreter','Latex');


else

figure('color', 'white');
plot(t(fs:end), Vin(fs:end), 'b', 'LineWidth', 2, 'DisplayName', 'Real op-amps');

hold on
aligned=Vout;
plot(t(fs:end),aligned(fs:end) , 'r--', 'LineWidth', 2, 'DisplayName', 'Ideal op-amps');

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
loglog(f, 20*log10(P1_in), 'b', 'LineWidth', 2, 'DisplayName', 'Real op-amps');
xlim([20, 20e3]);
ylim([-120, -25]);
hold on
%figure('color', 'white');
loglog(f1, 20*log10(P1), 'r--', 'LineWidth', 2, 'DisplayName', 'Ideal op-amps');
xlim([20, 20e3]);
ylim([-120, -25]);
ylabel('\bf Voltage [V]','interpreter','latex','FontSize',13)
xlabel('\bf Time [S]','interpreter','latex','FontSize',13)
ax = gca;
ax.FontSize = 13;
l = legend('show','FontSize',15);
set(l,'Interpreter','Latex');

end