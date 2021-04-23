%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% MRAC
% Input theta_l     : Load angular position
% Input theta_l_dot : Load angular velocity
% Input theta_m     : Motor angular position
% Input theta_m_dot : Motor angular velocity
% Input theta_m_d   : Motor desired angular position
% Input phi_k_1     : Prior system estimated parameters [L^T M Ks_hat Ds_hat]
% Input theta_r_k_1 : Prior reference model state variables
% Output tau_m   : Control torque
% Output phi_k   : Current estimated system parameters
% Output theta_r : Current reference model  state variables
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% function [V_control, phi_k, theta_r]  = mrac(theta_l, theta_l_dot, theta_m, theta_m_dot,... 
%                       theta_m_d, phi_k_1, theta_r_k_1, gamma, Kv, N, T, xi, w_n, q1, q2)
function [V_control, phi_k, theta_r]  = mrac(theta_l, theta_l_dot, theta_m, theta_m_dot,... 
                      theta_m_d, phi_k_1, theta_r_k_1)
	assert(isa(theta_l,'double') && isa(theta_l_dot,'double')...
        && isa(theta_m,'double') && isa(theta_m_dot,'double')...
        && isa(theta_m_d,'double'));
    assert(isa(phi_k_1,'double') && isa(theta_r_k_1,'double'));
    assert(all(size(phi_k_1) == [5 1]));
    assert(all(size(theta_r_k_1) == [2 1]));
%     assert(isa(gamma,'double') && isa(Kv,'double') && isa(N,'double') && isa(T,'double')...
%        && isa(xi,'double') && isa(w_n,'double')&& isa(q1,'double')&& isa(q2,'double'));
%%%%%%%%%% Local variable %%%%%%%%%%
    gamma = 0.995; % Learning rate coefficient
    % lon --> cham thich nghi, it gai
    % nho --> tn nhanh, co the nhieu
    Kv = 1;
    N = 10; % Gear ratio
    T = 0.001; % Sampling period
    xi = 1; % Damping ratio
    w_n = 5; % Natural frequency
    q1 = 3;
    q2 = 5;
    p2 = q1/(2*(w_n^2));
    p3 = (2*p2+q2)/(4*xi*w_n);
    p1 = 2*xi*w_n*p2 + (w_n^2)*p3;
    P = [p1 p2
         p2 p3];
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Reference Model %%%%%%%%%
    a1 = -T*(w_n^2); % -T*(w_n^2)
    a2 = 1-2*T*xi*w_n; % 1-2*T*xi*w_n
    Ad = [1  T
          a1 a2];
    b = T*(w_n^2); % T*(w_n^2)
    Bd = [0
          b];
    theta_r = Ad*theta_r_k_1 + Bd*theta_m_d; % Reference model

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Adaption Law %%%%%%%%%
    theta = [theta_m
             theta_m_dot]; % State variable
    e = theta - theta_r; % Error between System respond and reference model respond
    
    B = [0
         (w_n^2)/phi_k_1(3)];
    psi = B*[(-theta')   theta_m_d   ((-1/N)*theta_l)   ((-1/N)*theta_l_dot)]; % Regressor
    phi_dot = -gamma*psi'*P*e; % Derivative of parameters calculated from parameter
                               % adaption law
    phi_k = phi_k_1 + T*phi_dot; % Appoximated parameters calculated from its derivative
                                 % [L^T M Ks_hat Ds_hat]
    L = [phi_k(1)   phi_k(2)];
    M = phi_k(3);
    Ks_hat = phi_k(4);
    Ds_hat = phi_k(5);

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    

%%%%%%%%% Control Signal %%%%%%%%%
    V_control = Kv*(-L*theta + M*theta_m_d - Ks_hat*(1/N)*theta_l - Ds_hat*(1/N)*theta_l_dot);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
