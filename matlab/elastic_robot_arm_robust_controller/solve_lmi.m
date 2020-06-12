clear
clc

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Robot arm parameters
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Link length
l0 = 0.3;
l1 = 0.3;
% Link and motor mass
ml0 = 7.2;
ml1 = 3.2;
mm0 = 1;
mm1 = 1;
% Link and motor inertia
Ilxx0 = 0;
Ilyy0 = 0;
Ilzz0 = 0.1;
Ilxx1 = 0;
Ilyy1 = 0;
Ilzz1 = 0.1;
Im0 = 0.003;
Im1 = 0.003;
% Link and motor damping coefficient
Dm0 = 0.027;
Dm1 = 0.027;
Dl0 = 0.2;
Dl1 = 0.2;
% Gravitational constant
g = 9.81;
% String stiffness and damping coefficient
K0 = 1200;
K1 = 1440;
% Gear ratio
N0 = 10;
N1 = 10;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Dynamic matrices
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Joint angles and velocity
q0 = 0;
q1 = 0;
qdot0 = 0;
qdot1 = 0;

% String stiffness
K = [K0 0
     0  K1];

% Mass matrix
M = [Ilzz0 + Ilzz1 + (l1^2*ml1)/4 - (l1^2*ml1*sin(q1)^2)/4   0
     0                                                       Ilyy1 + (l1^2*ml1)/4 + Ilxx1*sin(q0)^2 - Ilyy1*sin(q0)^2];

% Centrifugal and Coriolis forces
C = zeros(2,1);
C(1,1) = - qdot1*((ml1*qdot0*sin(2*q1)*l1^2)/8 + (qdot1*sin(2*q0)*(Ilxx1 - Ilyy1))/2) - (l1^2*ml1*qdot0*qdot1*sin(2*q1))/8;
C(2,1) = (l1^2*ml1*qdot0^2*sin(2*q1))/8 + Ilxx1*qdot0*qdot1*sin(2*q0) - Ilyy1*qdot0*qdot1*sin(2*q0);

% Gravitational forces
G = zeros(2,1);
G(1,1) = 0;
G(2,1) = ml1*g*(l1/2)*cos(q1);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Performance matrices
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Note that the performance level is determined by gamma and weighting matrix H
% and that the control-input energy can be adjusted by matrix D.
gamma = 0.01;
H = [0.1 0   
     0   0.1
     0   0
     0   0];
D = [0 0
     0 0
     3 0
     0 3];

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Solving LMI
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
setlmis([])

Q = lmivar(1,[2 1]);

% Positive definite matrix Q
lmiterm([-1 1 1 Q], 1, 1); % Q > 0

% LMI
lmiterm([2 1 1 Q], -C, M.','s'); % -C*Q*M' - M*Q'*C'
lmiterm([2 1 1 0], 1/((gamma)^2)); % 1/((gamma)^2))*I
lmiterm([2 1 1 0], -K*inv((D.')*D)*(K.')); % -K*[D'*D]^(-1)*K'

lmiterm([2 2 1 Q], H, M.')

lmiterm([2 2 2 0], -1);

LMISYS = getlmis;
[tmin,Qsol]=feasp(LMISYS);
Q=dec2mat(LMISYS,Qsol,Q)

P = inv(Q)
