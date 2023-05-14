
function Vout = shiftingStageNL(input, Ts)

N = length(input);
Vref = 5.1;
Is = 5.185e-3;
Vp = -2.021;
k = 2 * Is / Vp^2;
k2=4e-3*Is/Vp^2;

%% LFO accurato
fs = 1/Ts; % Frequenza di campionamento
T = N/fs; % Durata del segnale
f = 1; % Frequenza del segnale triangolare
A = 0.15; % Ampiezza del segnale triangolare

% Generazione del segnale triangolare
t = 0:1/fs:T-1/fs;
x = A * sawtooth(2*pi*f*t, 0.6);
% x_s = A * square(2*pi*f*t, 75);

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

Vg = filter(hpFilt, y) + 3.25;
Vg=3.08;




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
             -1 0 -1 0
             0 1 0 0
             0 0 0 0
             -1 -1 0 -1].';

a = zeros(size(Qv,2),1);
b = zeros(size(Qv,2),1);
b_old=0;

Z1 = 1e-6;
Z2 = 24e3;
Z3 = 10e3;
Z4 = Ts/(2*47e-9);
Z5 = Z3;
Z7 = 1e9;
Z8 = 1e-6;

Vout = zeros(N,1);
Vds=0;
for n = 1 : N
 

%  Z6 = 1 / (k * (Vg - Vref - Vp));

syms Z6;
Z = diag([Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8]);
S = 2*Qv'*((Qi/Z*Qv')\(Qi/Z)) - eye(size(Qv,2));

Z6solved = eval(solve(S(6,6)==0,Z6));

Z=diag([Z1 Z2 Z3 Z4 Z5 Z6solved Z7 Z8]);
S = 2*Qv'*((Qi/Z*Qv')\(Qi/Z)) - eye(size(Qv,2));




    a(1) = -input(n); 
    a(4) = b_old;
    a(6) = 
    a(8) = Vref;

    b = S*a;
    
    b_old = b(4);

    Vout(n) = (a(7) + b(7))/2;
    Vds = (a(2)+b(2))/2;
 
end

end

