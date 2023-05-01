
function Vout = inputStage(input, Ts)

N=length(input);
Vref=5.1;
  
      Qv=[1 0
          0 1
          -1 -1
          -1 -1].';
      Qi=[1 0
          0 1
          0 0
          -1 -1].';

a = zeros(size(Qv,2),1);
b = zeros(size(Qv,2),1);

Z1 = 10e3;
Z2 = Ts/(2*0.01e-6);
Z3 = 1e9;
Z4 = 470e3;


Z = diag([Z1 Z2 Z3 Z4]);

S = 2*Qv'*((Qi/Z*Qv')\(Qi/Z)) - eye(size(Qv,2));

Vout = zeros(N,1);

% b_old=0;
% 
% for n = 1 : N
%     a(2) = b_old;
%     a(4) = Vref;
% 
%     b = S*a;
%     
%     b_old = b(2);
% end

b_old=-5.1;
for n = 1 : N

    a(1) = -input(n); 
    a(2) = b_old;
    a(4) = Vref;

    b = S*a;
    
    b_old = b(2);

    Vout(n) = (a(3) + b(3))/2;
    
end

end

