clear
clc
close all

l1 = 0.165;
l2 = 0.2;
    
% Calculate trajectory
q1d = linspace(0, pi, 1000);
q2d = linspace(3*pi/4, 7*pi/6, 1000);
xd = l2.*cos(q1d).*cos(q2d);
yd = l2.*sin(q1d).*cos(q2d);
zd = l1+l2.*sin(q2d);

% % Inverse kinematics
% q1 = zeros(1, 1000);
% q2 = zeros(1, 1000);
% [q1(1), q2(1)] = inverse_kinematics(xd(1), yd(1), zd(1), 0);
% for i=2:1000
%    [q1(i), q2(i)] = inverse_kinematics(xd(i), yd(i), zd(i), q1(i-1));
% end
% 
% % Forward kinematics:
% x = l2.*cos(q1).*cos(q2);
% y = l2.*sin(q1).*cos(q2);
% z = l1 + l2.*sin(q2);

% Plot trajectory
plot(xd, yd);
% hold on;
% plot3(x, y, z, 'r');
grid on;
