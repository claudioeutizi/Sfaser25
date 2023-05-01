
function Vout = shiftingStage(input, Ts)


N=length(input);
Vref=5.1;

      
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

Z1 = 1e-6;
Z2 = 24e3;
Z3 = 10e3;
Z4 = Ts/(2*47e-9);
Z5 = Z3;
Z6 = 414;
Z7 = 1e9;
Z8 = 1e-6;

Z = diag([Z1 Z2 Z3 Z4 Z5 Z6 Z7 Z8]);

S = 2*Qv'*((Qi/Z*Qv')\(Qi/Z)) - eye(size(Qv,2));

Vout = zeros(N,1);

% for n = 1 : N
%     a(1) = -5.1;
%     a(4) = b_old;
%     a(8) = Vref;
% 
%     b = S*a;
%     
%     b_old = b(4);
%     
% end

b_old=0;

for n = 1 : N

    a(1) = -input(n); 
    a(4) = b_old;
    a(8) = Vref;

    b = S*a;
    
    b_old = b(4);

    Vout(n) = (a(7) + b(7))/2;
 
end

end

