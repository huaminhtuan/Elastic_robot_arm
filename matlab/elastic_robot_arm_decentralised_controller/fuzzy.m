%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Fuzzy
% Input e_l_k        : Current error between load angular position feedback and 
%                      desired load angular position
% Input e_l_k_1      : Prior error between load angular position feedback and
%                      desired load angular position
% Input theta_m_d_k_1: Prior desired motor angular position
% Output theta_m_d: Desired motor position
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function theta_d = fuzzy(e_l_k, e_l_k_1, theta_d_k_1)
    assert(isa(e_l_k,'double') && isa(e_l_k_1,'double')...
        && isa(theta_d_k_1,'double'));
%%%%%%%%%% Local variable %%%%%%%%%%
    Kp = 5;
    Kd = 0.1;
    Ku = 1;
    T = 0.001;
    theta_d_upper_limit = pi;
    theta_d_lower_limit = -pi;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Preprocessing %%%%%%%%%
    e = Kp*e_l_k;
    de = Kd*(e_l_k - e_l_k_1)/T;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Fuzzification %%%%%%%%%
%%%
% Input e
% 	Range: [-1  1]
%	Membership functions: NB, NS, ZE, PS, PB
% Input de:
%	Range: [-1  1]
%	Membership functions: NB, NS, ZE, PS, PB
%%%
%
	fuzzy_e = zeros(1,5); % 1 to 5: NB, NS, ZE, PS, PB
    fuzzy_de = zeros(1,5); % 1 to 5: NB, NS, ZE, PS, PB
% Out of range
	if e < -1
		fuzzy_e(1) = 1; % NB
	elseif e > 1
		fuzzy_e(5) = 1; % PB
	else
		fuzzy_e(1) = trapmf(e, [-2.8 -1.2 -0.4 -0.2]); % NB
		fuzzy_e(2) = trimf(e, [-0.4 -0.2 0]); % NS
		fuzzy_e(3) = trimf(e, [-0.2 0 0.2]); % ZE
		fuzzy_e(4) = trimf(e, [0 0.2 0.4]); % PS
		fuzzy_e(5) = trapmf(e, [0.2 0.4 1.2 2.8]); % PB
	end

	if de < -1
		fuzzy_de(1) = 1; % NB
	elseif de > 1
		fuzzy_de(5) = 1; % PB
	else
		fuzzy_de(1) = trapmf(de, [-2.8 -1.2 -0.3 -0.1]); % NB
		fuzzy_de(2) = trimf(de, [-0.3 -0.1 0]); % NS
		fuzzy_de(3) = trimf(de, [-0.1 0 0.1]); % ZE
		fuzzy_de(4) = trimf(de, [0 0.1 0.3]); % PS
		fuzzy_de(5) = trapmf(de, [0.1 0.3 1.2 2.8]); % PB
	end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Fuzzy Inference Rules %%%%%%%%%
%%%
% ------------------------------
% | \e|    |    |    |    |    |
% |de\| NB | NS | ZE | PS | PB |
% |-----------------------------
% |	NB| PB | PB | PB | PS | ZE |
% |-----------------------------
% | NS| PB | PB | PS | ZE | NS |
% |-----------------------------
% | ZE| PB | PS | ZE | NS | NB |
% |-----------------------------
% | PS| PS | ZE | NS | NB | NB |
% |-----------------------------
% | PB| ZE | NS | NB | NB | NB |
% ------------------------------
% MAX-PROD aggregation rules
%%%
% Firing strength
    rules = zeros(5,5);
    for i=1:5
        for j=1:5
            rules(i,j) = fuzzy_de(i)*fuzzy_e(j);
        end
    end
% Accummulation
    u_PB = max([rules(1,1)  rules(1,2)  rules(1,3)  rules(2,1)  rules(2,2)  rules(3,1)]);
    u_PS = max([rules(1,4)  rules(2,3)  rules(3,2)  rules(4,1)]);
    u_ZE = max([rules(1,5)  rules(2,4)  rules(3,3)  rules(4,2)  rules(5,1)]);
    u_NS = max([rules(2,5)  rules(3,4)  rules(4,3)  rules(5,2)]);
    u_NB = max([rules(3,5)  rules(4,4)  rules(4,5)  rules(5,3)  rules(5,4)  rules(5,5)]);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Defuzzification %%%%%%%%%
%%%
% Defuzzification method: Center of gravity
%%%
    tmp1 = u_PB*1 + u_PS*0.3 + u_ZE*0 + u_NS*(-0.3) + u_NB*(-1);
    tmp2 = u_PB + u_PS + u_ZE + u_NS + u_NB;
    u = tmp1/tmp2;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Postprocessing %%%%%%%%%
    theta_d = u*T + theta_d_k_1;
    theta_d = theta_d*Ku;
    % Saturation
    if theta_d > theta_d_upper_limit
        theta_d = theta_d_upper_limit;
    elseif theta_d < theta_d_lower_limit
        theta_d = theta_d_lower_limit;
    end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
