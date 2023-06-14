%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Sliding mode controller
% Input :
% Output theta_d: Desired motor position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [theta_d, W_k, delta_phi_k] = asmc(e, edot, q, qdot, qddot, qddotdot, W_k_1, delta_phi_k_1)
    assert(isa(e,'double') && isa(edot,'double') &&...
           isa(q,'double') && isa(qdot,'double') &&...
           isa(qddot,'double') && isa(qddotdot,'double') &&...
           isa(W_k_1,'double') && isa(delta_phi_k_1,'double'));
    
    assert(all(size(e) == [2 1]));
    assert(all(size(edot) == [2 1]));
    assert(all(size(q) == [2 1]));
    assert(all(size(qdot) == [2 1]));
    assert(all(size(qddot) == [2 1]));
    assert(all(size(qddotdot) == [2 1]));
    assert(all(size(qddotdot) == [2 1]));
    assert(all(size(W_k_1) == [2 1]));
    assert(all(size(delta_phi_k_1) == [2 5]));

%%%%%%%%%% Local variable %%%%%%%%%%
    Ke = [1 0
          0 1];
    Ksigma = 1;
    T = 0.001;
    U = 100;
    error_deadzone = 0.174533;
    error_dot_deadzone = 0.523599;
    A = (1.0e-04)*[0.5 0
                   0   0.5];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

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

%%%%%%%%% Dynamic matrices %%%%%%%%%
    q0 = q(1);
    q1 = q(2);
    qdot0 = qdot(1);
    qdot1 = qdot(2);
    
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
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Control variable %%%%%%%%%
    s = edot + Ke*e; % Sliding surface
    W_k = W_k_1 - 1.1*U*tanh(Ksigma*s)*T;
    u = -sqrt(U).*sqrt(abs(s)).*tanh(Ksigma*s) + W_k; % Control variable
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%% Adaption Law %%%%%%%%%%%
    if e(1) < error_deadzone && e(2) < error_deadzone...
            && edot(1) < error_dot_deadzone...
            && edot(2) < error_dot_deadzone
        delta_phi_dot = zeros(size(delta_phi_k_1));
    else
        psi = [-(qddotdot + Ke*qddot - u)
           -qdot
           -1];
        delta_phi_dot = -A*s*psi';
    end
    delta_phi_k = delta_phi_k_1 + delta_phi_dot*T;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%% Control signal %%%%%%%%%%
    theta_d = (inv(K_hat)*M_hat + delta_phi_k(:,1:2))*(qddotdot + Ke*qddot - u) +...
              (inv(K_hat)*(C_hat-M_hat*Ke) + delta_phi_k(:,3:4))*qdot +...
              (inv(K_hat)*G_hat + delta_phi_k(:,5)) + q;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
