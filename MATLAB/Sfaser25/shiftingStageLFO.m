
function Vout = shiftingStageLFO(input, Ts)

N = length(input);
Vref = 5.1;
Is = 5.367e-3;
Vp = -2.021;
k = 2 * Is / Vp^2;

lambda = 4e-3;

speed = 2;
sample_rate = 1/Ts;
lfoIndex = 0:Ts:N/sample_rate-Ts;
dutyCycle = 0.65;

%% LFO
lfoType='tri'; 


if strcmp(lfoType, 'sine')
    lfoValue = sin(lfoIndex * 2 * 3.1415 * speed) * 0.15 + 3.25;
end

if strcmp(lfoType, 'tri')
        
    lfoValue=zeros(1,sample_rate/speed);

    for lfoIndex=1:(sample_rate+1)/speed
        index=lfoIndex*speed/sample_rate;
        if (index < dutyCycle) 
            lfoValue(lfoIndex)= (index*0.3) / dutyCycle+3.1;
    
        else 
            lfoValue(lfoIndex)=  0.3 / (1 - dutyCycle)*(-index + 1)+3.1;
   
        end
    end
%     plot(lfoValue);
end

%% Static parameters

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
%ZArray=zeros(N,1);

%% Iterative update
for n = 1 : N
    j=mod(n-1,length(lfoValue))+1;
 
    if Vds < lfoValue(j) - 5.1 - Vp

        Z6 = 1 / (k * (lfoValue(j) - Vref - Vp - Vds/2) );
    else 
        Z6 = Vds/(Is*(1-(lfoValue(j)-Vref)/Vp)^2*(1+lambda*Vds));
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
    %ZArray(n) = Z6;
    Vds=(a(6)+b(6))/2;

    Vout(n) = (a(7) + b(7))/2;
end
    %%Store variables to plot
    %plot(VdsArray, IdsArray);
    %save('variables', 'VdsArray', 'IdsArray', 'ZArray');
end

