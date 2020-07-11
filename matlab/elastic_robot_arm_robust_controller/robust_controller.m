%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Robust Controller
% Input :
% Output theta_m_d: Desired motor position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [theta_d, q_r_dot_k, integral] = robust_controller(q_d, q_d_prev, q, qdot, q_r_dot_prev, integral_prev)
    assert(isa(q_d,'double') && isa(q_d_prev,'double') &&...
           isa(q,'double') && isa(qdot,'double') && isa(q_r_dot_prev,'double') &&...
           isa(integral_prev,'double'));
    assert(all(size(q_d) == [2 1]));
    assert(all(size(q_d_prev) == [2 1]));
    assert(all(size(q) == [2 1]));
    assert(all(size(qdot) == [2 1]));
    assert(all(size(q_r_dot_prev) == [2 1]));
    assert(all(size(integral_prev) == [2 1]));
%%%%%%% Robot arm parameters %%%%%%%
    % Link length
    l0 = 0.3;
    l1 = 0.3;
    % Link and motor mass
    ml0 = 6;
    ml1 = 4;
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
    K0 = 1500;
    K1 = 1200;
    % Gear ratio
    N0 = 10;
    N1 = 10;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% Calculate dynamic matrices %%%%
    T = 0.001; % Sampling period
    q0 = q(1);
    q1 = q(2);
    qdot0 = qdot(1);
    qdot1 = qdot(2);
    Kp = 15;
    Ki = 3;
    K_hat = [K0 0
             0  K1];
    M_hat = [Ilzz0 + Ilzz1 + (l1^2*ml1)/4 - (l1^2*ml1*sin(q1)^2)/4  0
             0,                                                     Ilyy1 + (l1^2*ml1)/4 + Ilxx1*sin(q0)^2 - Ilyy1*sin(q0)^2];
    C_hat = zeros(2,2);
    C_hat(1,1) = -(l1^2*ml1*qdot1*sin(2*q1))/8;
    C_hat(1,2) = -(qdot1*sin(2*q0)*(Ilxx1 - Ilyy1))/2;
    C_hat(2,1) = (qdot1*sin(2*q0)*(Ilxx1 - Ilyy1))/2;
    C_hat(2,2) = 0;
    
    G_hat = zeros(2,1);
    G_hat(1,1) = 0;
    G_hat(2,1) = ml1*g*(l1/2)*cos(q1);

    P = 1.0e-04*[0.2152         0
                      0    0.0959];

    D = [0 0
         0 0
         1 0
         0 1];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% Calculate reference signal %%%%
    q_d_dot_k = (q_d - q_d_prev)/T;
    error = q - q_d;
    integral = integral_prev + error*T;
    q_r_dot_k = q_d_dot_k - Kp*error - Ki*integral;
    q_r_dotdot_k = (q_r_dot_k - q_r_dot_prev)/T;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%% Calculate control input ut %%%%
    ut = inv(K_hat)*(M_hat*q_r_dotdot_k + C_hat*q_r_dot_k + G_hat) + q;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%% Calculate new state %%%%%%%%
    s = qdot - q_r_dot_k;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Calculate robust control input ur %
    B2 = inv(M_hat)*K_hat;
    ur = -inv((D.')*D)*(B2.')*P*s;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%% Calculate motor desired angle %%
    theta_d = ut + ur;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
