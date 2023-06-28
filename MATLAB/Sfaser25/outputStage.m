
function Vout = outputStage(inputDry, inputWet, Ts)


N=length(inputDry);

      
      Qv=[1 0 0
          0 1 0
          0 0 1
          -1 -1 0
          1 0 0
          -1 -1 -1].';
      Qi=Qv;

a = zeros(size(Qv,2),1);
b = zeros(size(Qv,2),1);

Z1 = 150e3;
Z2 = Z1;
Z3 = Ts/(2*47e-9);
Z4 = 56e3;
Z5 = Z1;
Z6 = Z1;


Z = diag([Z1 Z2 Z3 Z4 Z5 Z6]);

S = 2*Qv'*((Qi/Z*Qv')\(Qi/Z)) - eye(size(Qv,2));

Vout = zeros(N,1);

b_old=1.01637;
for n = 1 : N

    a(1) = -inputWet(n); 
    a(5) = -inputDry(n);
    a(3) = b_old;
 

    b = S*a;
    
    b_old = b(3);

    Vout(n) = (a(6) + b(6))/2;
end

end

