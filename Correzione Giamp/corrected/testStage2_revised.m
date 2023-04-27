clear;
close all;
clc;


f0 = 440;
fs = 44100;
Ts = 1/fs;
StopTime = 5/f0;
t = 0:Ts:StopTime;
%[Vin,fs] = audioread('sine440.wav');
Vin = sin(2*pi*f0*t);
% Vin=(Vin(:,1)+Vin(:,2))/2;
N=length(Vin);
Vref=5.1;


% Qv=[1 0 0 -1 -1 0 0;
%     0 1 0  1 1 1 1;
%     0 0  1 0 0 0 1];
% 
% Qi=[1 0 0 -1 -1 0 0;
%     0 1 0 0 1 1 0;
%     0 0 1 1 0 0 0 ];

      
      Qv=[1 0 0 0
             0 1 0 0
             0 0 1 0
             0 0 0 1
             0 0 0 1
             0 1 0 0
             -1 0 -1 -1
             -1 -1 0 -1].';
      Qi=[1 0 0 0
             0 1 0 0
             0 0 1 0
             0 0 0 1
             1 0 -1 0
             0 1 0 0
             0 0 0 0
             -1 -1 0 -1].';

a2=0;
a3=0;
b4=0;
a5=0;
a6=0;
a7=0;

a = zeros(8,1);
b = zeros(8,1);

Z1 = 1;
Z2 = 24e3;
Z3 = 10e3;
Z4 = Ts/(2*47e-9);
Z5 = Z3;
Z6 = 1e-3;
Z7 = 5e3;
Z8 = 1e-6;

% syms Z8 real

Z = diag([Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8]);

% S=2 * Qv.' * inv(Qi * inv(Z) * Qv.') * Qi * inv(Z) - eye(size(Qv,2));
% 
% Z8solved = eval(solve(S(8,8)==0,Z8));

% Z=diag([Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8solved]);

% S = 2 * Qv.' * inv(Qi * inv(Z) * Qv.') * Qi * inv(Z) - eye(size(Qv,2));
S = 2*Qv'*((Qi/Z*Qv')\(Qi/Z)) - eye(8);


Vout = zeros(N,1);
a_old = -5.0214; % initialization of memory
%i=1;
%a8=0;

for n = 1 : N

    b(1) = -Vin(n); % la direzione che avete messo sulla porta uno non è corretta rispetto la polarità del generatore, perciò ho messo un -
    b(4) = a_old;
    b(8) = Vref;

    a = S*b;

%     a4=b4;
%     
%     b1=S(1,:)*[0 a2 a3 a4 a5 a6 a7 a8].';
%     b8=S(8,:)*[0 a2 a3 a4 a5 a6 a7 a8].';
%     
%     a1=2*Vin(i)-b1;
%     a8=2*Vref-b8;
%     
%     b4=S(4,:)*[a1 a2 a3 a4 a5 a6 a7 a8].';
%     b7=S(7,:)*[a1 a2 a3 a4 a5 a6 a7 a8].';
    
    a_old = a(4);

    Vout(n) = (a(7) + b(7))/2;
    
end

%% Load LTspice DATA

loadedFile = load('Vout.txt');
t_spice = loadedFile(:,1);
V_spice = loadedFile(:,2);

%%

figure('color', 'white');
%plot(Vin);
%hold on; 
plot(t, Vout, 'b', 'LineWidth', 2, 'DisplayName', 'WDF');
hold on
plot(t_spice, V_spice, 'r--', 'LineWidth', 2, 'DisplayName', 'LTspice');
ylabel('\bf Voltage [V]','interpreter','latex','FontSize',13)
xlabel('\bf Time [S]','interpreter','latex','FontSize',13)
ax = gca;
ax.FontSize = 13;
l = legend('show','FontSize',15);
set(l,'Interpreter','Latex');


