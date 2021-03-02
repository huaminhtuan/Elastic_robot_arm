clear
clc
close all

% get data
fid_joint_1 = fopen('log_kin_joint_1_disturb.txt');
line_joint_1 = fgetl(fid_joint_1);
fid_joint_2 = fopen('log_kin_joint_2_disturb.txt');
line_joint_2 = fgetl(fid_joint_2);
id = 1;

num_line = 9000;

load_angle_joint_1 = zeros(1,num_line);
motor_angle_joint_1 = zeros(1,num_line);
control_voltage_joint_1 = zeros(1,num_line);
motor_desired_angle_joint_1 = zeros(1,num_line);

load_angle_joint_2 = zeros(1,num_line);
motor_angle_joint_2 = zeros(1,num_line);
control_voltage_joint_2 = zeros(1,num_line);
motor_desired_angle_joint_2 = zeros(1,num_line);

while true
    data = strsplit(line_joint_1);
    load_angle_joint_1(id) = str2double(data(3));
    motor_angle_joint_1(id) = str2double(data(4))/4;
    control_voltage_joint_1(id) = str2double(data(5));
    motor_desired_angle_joint_1(id) = str2double(data(6))/4;
    
    data = strsplit(line_joint_2);
    load_angle_joint_2(id) = str2double(data(3));
    motor_angle_joint_2(id) = str2double(data(4))/4;
    control_voltage_joint_2(id) = str2double(data(5));
    motor_desired_angle_joint_2(id) = str2double(data(6))/4;
    
    id = id + 1;
    if id>num_line
        break;
    end
    line_joint_1 = fgetl(fid_joint_1);
    line_joint_2 = fgetl(fid_joint_2);
end
fclose(fid_joint_1);
fclose(fid_joint_2);

% Calculate trajectory
l1 = 0.165;
l2 = 0.2;

q1d = [zeros(1,6000), linspace(0, pi, 1000), ones(1,num_line-7000)*(pi)];
q2d = [ones(1,3000)*(pi/2), ones(1,3000)*(3*pi/4), linspace(3*pi/4, 7*pi/6, 1000), ones(1,num_line-7000)*(7*pi/6)];
xd = l2.*cos(q1d).*cos(q2d);
yd = l2.*sin(q1d).*cos(q2d);
zd = l1+l2.*sin(q2d);

x = l2.*cos(load_angle_joint_1).*cos(load_angle_joint_2);
y = l2.*sin(load_angle_joint_1).*cos(load_angle_joint_2);
z = l1+l2.*sin(load_angle_joint_2);

% Plot trajectory
time = -60:0.01:(num_line/100-0.01-60);
figure;
plot3(xd(6001:8000), yd(6001:8000), zd(6001:8000), '--b');
hold on;
plot3(x(6001:8000), y(6001:8000), z(6001:8000), 'r');
title('trajectory plot');
legend('desired trajectory', 'real trajectory');
xlabel('x (m)', 'Rotation',20);
ylabel('y (m)', 'Rotation',-30);
zlabel('z (m)');
grid on;

figure;
plot(time(6001:8000), sqrt((x(6001:8000)-xd(6001:8000)).*(x(6001:8000)-xd(6001:8000)) +...
                (y(6001:8000)-yd(6001:8000)).*(y(6001:8000)-yd(6001:8000)) +...
                (z(6001:8000)-zd(6001:8000)).*(z(6001:8000)-zd(6001:8000))), 'k');
title('trajectory tracking error');
legend('error');
xlabel('time (s)');
ylabel('distance (m)');
grid on;

% Plot response
figure;
subplot(2,1,1);
plot(time(6001:8000), load_angle_joint_1(6001:8000), 'r');
hold on;
plot(time(6001:8000), q1d(6001:8000), '--b');
hold on;
% plot(time, motor_desired_angle_joint_1, 'g');
% hold on;
% plot(time, motor_angle_joint_1, 'b');
title('load angle joint 1');
legend('load angle', 'desired load angle');
ylabel('angle (rad)');
grid on;
subplot(2,1,2);
plot(time(6001:8000), (load_angle_joint_1(6001:8000)-q1d(6001:8000)), 'k');
title('error: (load angle) - (desired load angle)');
legend('error');
xlabel('time (s)');
ylabel('error (rad)');
grid on;

% figure;
% subplot(2,1,1);
% plot(time, load_angle_joint_1, 'r');
% title('motor and load angle joint 1');
% hold on;
% plot(time, motor_angle_joint_1, '--b');
% grid on;
% subplot(2,1,2);
% plot(time, (load_angle_joint_1-motor_angle_joint_1), '-.k');
% grid on;

figure;
subplot(2,1,1);
plot(time(6001:8000), load_angle_joint_2(6001:8000), 'r');
hold on;
plot(time(6001:8000), q2d(6001:8000), '--b');
hold on;
% plot(time, motor_desired_angle_joint_2, 'g');
% hold on;
% plot(time, motor_angle_joint_2, 'b');
title('load angle joint 2');
legend('load angle', 'desired load angle');
ylabel('angle (rad)');
grid on;
subplot(2,1,2);
plot(time(6001:8000), (load_angle_joint_2(6001:8000)-q2d(6001:8000)), 'k');
title('error: (load angle) - (desired load angle)');
legend('error');
xlabel('time (s)');
ylabel('error (rad)');
grid on;

% figure;
% subplot(2,1,1);
% plot(time, load_angle_joint_2, 'r');
% title('motor and load angle joint 2');
% hold on;
% plot(time, motor_angle_joint_2, '--b');
% grid on;
% subplot(2,1,2);
% plot(time, (load_angle_joint_2-motor_angle_joint_2), '-.k');
% grid on;

% % Plot error
% figure;
% plot(time, (x-xd));
% title('x error');
% grid on;
% 
% figure;
% plot(time, (y-yd));
% title('y error');
% grid on;
% 
% figure;
% plot(time, (z-zd));
% title('z error');
% grid on;
