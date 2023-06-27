
function Vout = shiftingStageLFO(input, Ts)

N = length(input);
Vref = 5.1;
Is = 5.367e-3;
Vp = -2.021;
k = 2 * Is / Vp^2;

lambda = 4e-3;
k2 = (lambda * Is);

alpha=1;

speed = 0;
sample_rate = 1/Ts;
lfoIndex = 0:Ts:N/sample_rate-Ts;
lfoValue = sin(lfoIndex * 2 * 3.1415 * speed) * 0.15 + 3.25;
 
%% LFO accurato
% fs = 1/Ts; % Frequenza di campionamento
% T = N/fs; % Durata del segnale
% f = 7; % Frequenza del segnale triangolare
% A = 0.15; % Ampiezza del segnale triangolare
% 
% % Generazione del segnale triangolare
% t = 0:1/fs:T-1/fs;
% x = A * sawtooth(2*pi*f*t, 0.6);
% % x_s = A * square(2*pi*f*t, 75);
% 
% % Progettazione del filtro passa basso
% fc = 10; % Frequenza di taglio del filtro passa basso
% %N = 101; % Ordine del filtro
% %b = fir1(N, fc/(fs/2), 'low');
% 
% % Filtraggio del segnale triangolare
% %y = filter(b, 1, x);
% 
% lpFilt = designfilt('lowpassiir','FilterOrder',2, ...
%     'PassbandFrequency',fc,'PassbandRipple',0.4, ...
%     'SampleRate',fs);
% y = filter(lpFilt, x);
% 
% fc_hp = 0.6;
% hpFilt = designfilt('highpassiir','FilterOrder',2, ...
%     'PassbandFrequency',fc_hp,'PassbandRipple',0.4, ...
%     'SampleRate',fs);
% 
% Vg = filter(hpFilt, y) + 3.25;

% sample_rate = 1/Ts;
% speed = 1;
% dutyCycle = 0.65;
% 
% lfoValue=zeros(1,sample_rate/speed);

% for lfoIndex=1:(sample_rate+1)/speed
%     index=lfoIndex*speed/sample_rate;
%     if (index < dutyCycle) 
%         lfoValue(lfoIndex)= (index*0.3) / dutyCycle+3.1;
%     
%     else 
%         lfoValue(lfoIndex)=  0.3 / (1 - dutyCycle)*(-index + 1)+3.1;
%    
%     end
% end

% Vg=3.25;
% figure;
% plot(t,Vg);
% hold on; 
% plot(t, 1 ./ (k * (Vg - Vref - Vp)));



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
VdsArray=zeros(N,1);
IdsArray=zeros(N,1);
ZArray=zeros(N,1);
for n = 1 : N


 if Vds < lfoValue(n) - 5.1 - Vp

        Z6 = 1 / (k * (lfoValue(n) - Vref - Vp - Vds/2) );
 else 
%         Z6 = 1 / (k2 * (1-(lfoValue(n)-Vref)/Vp)^2);
        Z6 = Vds/(Is*(1-(lfoValue(n)-Vref)/Vp)^2*(1+lambda*Vds));
%     Z6=15790;
 end
%syms Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8;
Z = diag([Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8]);

S = 2*Qv'*((Qi/Z*Qv')\(Qi/Z)) - eye(size(Qv,2));


    a(1) = -input(n); 
    a(4) = b_old;
    a(8) = Vref;

    b = S*a;
    
    b_old = b(4);
    
    
    VdsArray(n) = Vds;
    IdsArray(n) = Vds/Z6;
    ZArray(n) = Z6;
    Vds=(a(6)+b(6))/2;


    Vout(n) = (a(7) + b(7))/2;
 


end
    plot(VdsArray, IdsArray);
    save('variables', 'VdsArray', 'IdsArray', 'ZArray');
end

