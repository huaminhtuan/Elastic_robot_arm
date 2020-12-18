clear
clc
close all

% get data
fid = fopen('log_j1_square_normal.txt');
line = fgetl(fid);
id = 1;

while ischar(line)
    data = strsplit(line);
    load_angle(id) = str2double(data(3));
    motor_angle(id) = str2double(data(4))/4;
    control_voltage(id) = str2double(data(5));
    
    id = id + 1;
    if id>40000
        break;
    end
    line = fgetl(fid);
end
fclose(fid);

% Plot

time = 0:0.01:((id-2)*0.01);

% ref = 0.5*sin((2*pi/50)*time);

s = size(time);
ref = zeros(1, s(2));
k = 0;
for i=1:s(2)
    if mod(i,2000)==0
        k=k+1;
        k = mod(k,4);
    end
    
    if k==0
        ref(i)=0.5;
    elseif k==1
        ref(i)=0;
    elseif k==2
        ref(i)=-0.5;
    elseif k==3
        ref(i)=0;
    end
end

plot(time, load_angle, 'r');
hold on;
plot(time, ref, 'b--');
hold on;
plot(time, motor_angle, 'black-.');
title('angle response');
legend('load angle', 'desired load angle', 'motor angle');
xlabel('time (s)');
ylabel('angle (radian)');
grid on;

figure;
plot(time, control_voltage, 'r');
title('voltage');
legend('control voltage');
xlabel('time (s)');
ylabel('voltage (V)');
grid on;



