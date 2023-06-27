close all;
clear;
clc;

load('variables.mat');

I_ds = load('I_ds.txt');
I_ds = I_ds(:,2);

V_ds = load('V_ds.txt');
V_ds = V_ds(:,2);

I_ds2 = load('I_ds3.2.txt');
I_ds2 = I_ds2(:,2);

V_ds2 = load('V_ds3.2.txt');
V_ds2 = V_ds2(:,2);

I_ds3 = load('I_ds3.3.txt');
I_ds3 = I_ds3(:,2);

V_ds3 = load('V_ds3.3.txt');
V_ds3 = V_ds3(:,2);

plot(V_ds, I_ds, 'b', 'LineWidth', 1, 'DisplayName', 'LTSpice');
hold on;
plot(V_ds2, I_ds2,  'b', 'LineWidth', 1);
hold on;
plot(V_ds3, I_ds3,  'b', 'LineWidth', 1);



hold on;
plot(VdsArray(450:end), IdsArray(450:end),  'r', 'LineWidth', 1);
% l = legend('show','FontSize',10);
% set(l,'Interpreter','Latex');

xlim([0,1]);
ylabel('\bf Ids [A]','interpreter','latex','FontSize',13)
xlabel('\bf Vds [V]','interpreter','latex','FontSize',13)
text(0.9,4.1e-5, 'Vgs = 3.25', 'Color', 'k', 'FontSize', 9)
text(0.9,6.67e-5, 'Vgs = 3.3', 'Color', 'k', 'FontSize', 9)
text(0.9,2.2e-5, 'Vgs = 3.2', 'Color', 'k', 'FontSize', 9)
