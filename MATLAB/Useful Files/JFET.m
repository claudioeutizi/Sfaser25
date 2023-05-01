clear;
close all;
clc;



Vp = -2.021;
I_s0 = 10e-3;

% Vgs = -1;

x1=0.8;


for i=0:0
    Vgs=-1;
    Vsat=Vgs-Vp;
    Vds = 0:0.01:Vsat;
    Id = (2*I_s0*(((Vgs-Vp)*Vds)-(Vds.^2)/2))/Vp^2;
    y1 = (2*I_s0*(((Vgs-Vp)*x1)-(x1^2)/2))/Vp^2;
    Rds = 2*I_s0/(Vp^2) * (Vgs-Vp - x1);
    plot(Vds, Id, 'blue');
    hold on;
%     plot(Vds, Rds*(Vds-x1)+y1, 'red');
    hold on;
end
figure;
for i=0:0
 Vgs=-1 
    plot(Vds,2*I_s0/(Vp^2) * (Vgs-Vp - Vds));
    hold on;
end
