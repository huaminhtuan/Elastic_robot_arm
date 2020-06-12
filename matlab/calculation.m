%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Calculate elastic robot arm's equations
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear
clc
% Number of joints
num_of_joints = 2;
% Link and motor variables
syms q0 q1 qdot0 qdot1 theta0 theta1 real
q = [q0; q1];
qdot = [qdot0; qdot1];
theta = [theta0 theta1];
% Link length
syms l0 l1 real
% Link and motor mass
syms ml0 ml1 mm0 mm1 real
% Link and motor inertia
syms Ilxx0 Ilyy0 Ilzz0 real
syms Ilxx1 Ilyy1 Ilzz1 real
% Gravitational constant
syms g
% String stiffness
syms K
% External and motor forces
syms tau_ext tau_m
% Motor inertia matrix
syms B0 B1

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% DH matrices
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
H1_0 = [[ cos(q0), 0,  sin(q0),  0]
        [ sin(q0), 0, -cos(q0),  0]
        [       0, 1,        0, l0]
        [       0, 0,        0,  1]];

H2_1 = [[ cos(q1),  0, -sin(q1), l1*cos(q1)]
        [ sin(q1),  0,  cos(q1), l1*sin(q1)]
        [       0, -1,        0,          0]
        [       0,  0,        0,          1]];
    
H2_0 = H1_0*H2_1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Link and motor center of mass coordinate
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Oc0_0 = [0;0;l0/2];
temp = H1_0*[(l1/2)*cos(q1); (l1/2)*sin(q1) ;0 ;1];
Oc1_0 = temp(1:3);

Om0_0 = [0;0;0];
Om1_0 = H1_0(1:3, 4); % O1_0

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Load jaconbian matrices
% Linear velocities
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% vl0
Jvl0_q0 = simplify(diff(Oc0_0, q0));
Jvl0_q1 = simplify(diff(Oc0_0, q1));
Jvl0 = [Jvl0_q0 Jvl0_q1];

% vl1
Jvl1_q0 = simplify(diff(Oc1_0, q0));
Jvl1_q1 = simplify(diff(Oc1_0, q1));
Jvl1 = [Jvl1_q0 Jvl1_q1];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Load jaconbian matrices
% Angular velocities
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
z0_0 = [0;0;1];
z1_0 = H1_0(1:3, 3);
zero_vector = [0;0;0];
Jwl0 = [z0_0 zero_vector];
Jwl1 = [z0_0 z1_0];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Motor jaconbian matrices
% Linear velocities
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% vm0
Jvm0_q0 = simplify(diff(Om0_0, q0));
Jvm0_q1 = simplify(diff(Om0_0, q1));
Jvm0 = [Jvm0_q0 Jvm0_q1];

% vm1
Jvm1_q0 = simplify(diff(Om1_0, q0));
Jvm1_q1 = simplify(diff(Om1_0, q1));
Jvm1 = [Jvm1_q0 Jvm1_q1];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Mass matrix
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
Il0 = [Ilxx0 0     0;
       0     Ilyy0 0;
       0     0     Ilzz0];
Il1 = [Ilxx1 0     0;
       0     Ilyy1 0;
       0     0     Ilzz1];
% M = [[ Ilzz0 + Ilzz1 + (l1^2*ml1)/4 - (l1^2*ml1*sin(q1)^2)/4,                                                        0]
%      [                                                     0, Ilyy1 + (l1^2*ml1)/4 + Ilxx1*sin(q0)^2 - Ilyy1*sin(q0)^2]]
M = simplify(ml0*(Jvl0'*Jvl0) + ml1*(Jvl1'*Jvl1) +...
             (Jwl0.'*Il0*Jwl0) + (Jwl1.'*Il1*Jwl1));
% mm0*(Jvm0'*Jvm0) + mm1*(Jvm1'*Jvm1)
         
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Centrifugal and Coriolis Forces
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
syms C
for k = 1:num_of_joints
    for j = 1:num_of_joints
        for i = 1:num_of_joints
            C(i,j,k) = 0.5*(simplify(diff(M(k,j), q(i))) + ...
                       simplify(diff(M(k,i), q(j))) - ...
                       simplify(diff(M(i,j), q(k))));
        end
    end
end

