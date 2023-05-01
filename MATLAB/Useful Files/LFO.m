clear;
close all;

% Impostazione dei parametri del segnale
fs = 192000; % Frequenza di campionamento
T = 1; % Durata del segnale
f = 0; % Frequenza del segnale triangolare
A = 0.9; % Ampiezza del segnale triangolare

% Generazione del segnale triangolare
t = 0:1/fs:T-1/fs;
x = A * sawtooth(2*pi*f*t, 0.6);
x_s = A * square(2*pi*f*t, 75);

% Progettazione del filtro passa basso
fc = 10; % Frequenza di taglio del filtro passa basso
%N = 101; % Ordine del filtro
%b = fir1(N, fc/(fs/2), 'low');

% Filtraggio del segnale triangolare
%y = filter(b, 1, x);

lpFilt = designfilt('lowpassiir','FilterOrder',2, ...
    'PassbandFrequency',fc,'PassbandRipple',0.4, ...
    'SampleRate',fs);
y = filter(lpFilt, x);

fc_hp = 0.6;
hpFilt = designfilt('highpassiir','FilterOrder',2, ...
    'PassbandFrequency',fc_hp,'PassbandRipple',0.4, ...
    'SampleRate',fs);

y_hp = filter(hpFilt, y);

% Plot del segnale triangolare e del segnale filtrato
subplot(2,1,1);
plot(t, x);
xlabel('Tempo (s)');
ylabel('Amplitude');
title('Segnale triangolare');
subplot(2,1,2);
plot(t, y_hp);
xlabel('Tempo (s)');
ylabel('Amplitude');
title('Segnale filtrato');