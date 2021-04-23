%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Sliding mode controller
% Input e       : Current error between load angular position feedback and 
%                 desired load angular position
% Input edot    : Current error change rate
% Input q       : Current load angular position
% Input qdot    : Current load angular velocity
% Input thetadot: Current motor angular velocity
% Input qddot   : Current desired load angular velocity
% Input qddotdot: Current desired load angular acceleration
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [theta_d, W] = smc(e, edot, q, qdot, theta, thetadot, theta_dk_1, qddot, qddotdot, prevW)
    assert(isa(e,'double') && isa(edot,'double') && isa(q,'double') && isa(qdot,'double')...
       && isa(theta,'double') && isa(thetadot,'double') && isa(qddot,'double') && isa(qddotdot,'double') && isa(prevW,'double'));
    assert(isa(theta_dk_1,'double'));
%%%%%%%%%% Local variable %%%%%%%%%%
    Ks = 1400; % Spring stiffness 
    Ds = 0.1; % Spring damping coefficient
    Jl = 0.1; % Load inertia
    Dl = 0.2; % Load damping coefficient
    N = 10; % Gear ratio
%     U = 10000; % Control variable amplitude
%     Kp = 0.3;
%     Kd = 0.001;
    U = 100000; % Control variable amplitude
    Kp = 1.1;
    Kd = 1.6;

%     Kp = (250)^2;
%     Kd = (1)^2;
%     U = 10;
    
    T = 0.001;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Control variable %%%%%%%%%
	s = Kd*edot + Kp*e; % Sliding surface
    W = prevW - 1.1*U*sign(s)*T;
    u = -sqrt(U)*sqrt(abs(s))*sign(s) + W; % Control variable
%     u = -U*tanh(s); % Control variable
%     s = Kp*(e^2) + Kd*(edot^2);
%     u = -U*(edot^2)*tanh(s);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%% Control signal %%%%%%%%%%
    theta_d = (Jl/(Kd*Ks*(N^(-1))))*(Kd*qddotdot + Kp*qddot + (Kd*Ks/Jl)*q +...
              ((Kd*(Ds+Dl)-Kp*Jl)/Jl)*qdot - (Kd*Ds/Jl)*(N^(-1))*thetadot - u);

%     theta_ddot = (Jl/(Kd*Ds*(N^(-1))))*(Kd*qddotdot + Kp*qddot + (Kd*Ks/Jl)*q +...
%                  ((Kd*(Ds+Dl)-Kp*Jl)/Jl)*qdot - (Kd*Ks/Jl)*(N^(-1))*theta - u);
%     theta_d = theta_dk_1 + theta_ddot*T;

%     theta_ddot = (Jl/(2*Kd*Ds*(N^(-1))))*(2*Kp*e +...
%         2*Kd*(qddotdot + (Ds+Dl)/Jl*qdot + (Ks/Jl)*q - (Ks*(N^(-1))/Jl)*theta) +...
%          U*edot*tanh(s));
%     theta_d = theta_dk_1 + theta_ddot*T;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

