%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Sliding mode controller
% Input :
% Output theta_d: Desired motor position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [theta_d, W_k, delta_phi_k] = asmc_improved(e, edot, ie, q, qdot, qddot, qddotdot, W_k_1, delta_phi_k_1)
    assert(isa(e,'double') && isa(edot,'double') && isa(ie,'double') &&...
           isa(q,'double') && isa(qdot,'double') &&...
           isa(qddot,'double') && isa(qddotdot,'double') &&...
           isa(W_k_1,'double') && isa(delta_phi_k_1,'double'));
    
    assert(all(size(e) == [2 1]));
    assert(all(size(edot) == [2 1]));
    assert(all(size(ie) == [2 1]));
    assert(all(size(q) == [2 1]));
    assert(all(size(qdot) == [2 1]));
    assert(all(size(qddot) == [2 1]));
    assert(all(size(qddotdot) == [2 1]));
    assert(all(size(qddotdot) == [2 1]));
    assert(all(size(W_k_1) == [2 1]));
    assert(all(size(delta_phi_k_1) == [2 3]));

%%%%%%%%%% Local variable %%%%%%%%%%
    Kp = [3 0
          0 3];
    Ki = [1 0
          0 1];
    Ksigma = 1;
    T = 0.001;
    U = 400;
    error_deadzone = 0.174533;
    error_dot_deadzone = 0.523599;
    A = (1.0e-04)*[0.005 0
                   0   0.005];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Control variable %%%%%%%%%
    s = edot + Kp*e + Ki*ie; % Sliding surface
    W_k = W_k_1 - 1.1*U*tanh(Ksigma*s)*T;
    u = -sqrt(U).*sqrt(abs(s)).*tanh(Ksigma*s) + W_k; % Control variable
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%% Adaption Law %%%%%%%%%%%
    if e(1) < error_deadzone && e(2) < error_deadzone...
            && edot(1) < error_dot_deadzone...
            && edot(2) < error_dot_deadzone
        delta_phi_dot = zeros(size(delta_phi_k_1));
    else
        psi = [(qddotdot + Kp*edot + Ki*e - u)
               1];
        delta_phi_dot = A*s*psi';
    end
    delta_phi_k = delta_phi_k_1 + delta_phi_dot*T;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%% Control signal %%%%%%%%%%
    theta_d = (delta_phi_k(:,1:2))*(qddotdot + Kp*edot + Ki*e - u) +...
              (delta_phi_k(:,3)) + q;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
