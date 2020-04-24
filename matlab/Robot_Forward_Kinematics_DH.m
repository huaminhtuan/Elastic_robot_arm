clc
% Input number of joint
number_of_joint = input('Number of joint: ');
% Create a cell to store the matrices
DH_matrices = cell(1,number_of_joint);
% Input Denavit-Hartenberg joint variables
for i = 1:number_of_joint
    fprintf('Homogeneous matrix H%d_%d\n', i, i-1);
    d = input('   d     = ');
    theta = input('   theta = ');
    a = input('   a     = ');
    alpha = input('   alpha = ');
    % Calculate Denavit-Hartenberg matrix for joint ith
    DH_matrices{i} = [cos(theta) -sin(theta)*cos(alpha)  sin(theta)*sin(alpha) a*cos(theta)
                      sin(theta)  cos(theta)*cos(alpha) -cos(theta)*sin(alpha) a*sin(theta)
                         0               sin(alpha)             cos(alpha)          d
                         0                   0                      0               1 ];
    DH_matrices{i} = simplify(DH_matrices{i});
    fprintf('   H%d_%d=\n', i, i-1);
    disp(DH_matrices{i});
end

% Calculate the end effector matrix
fprintf('Homogeneous matrix for end effector: \n');
H_end_effector = eye(4);
for i = 1:number_of_joint
    H_end_effector = H_end_effector*DH_matrices{i};
end
H_end_effector = simplify(H_end_effector);
disp(H_end_effector);

