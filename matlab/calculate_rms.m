%%
% Calculate RMS value of the error
%
s = size(e_smc);
N = s(1); % number of samples
temp_1 = 0; % temporary variable 1
temp_2 = 0; % temporary variable 2
for k=1:N
    temp_1 = temp_1 + e_smc(k,1)*e_smc(k,1);
    temp_2 = temp_2 + e_smc(k,2)*e_smc(k,2);
end

temp_1 = sqrt(temp_1/N);
fprintf("rms_e_1 = %f\n", temp_1);
temp_2 = sqrt(temp_2/N);
fprintf("rms_e_2 = %f\n", temp_2);

%%
% Calculate total variation value of the control voltage
%
s = size(v_smc);
N = s(1);
temp_1 = 0;
temp_2 = 0;
for k=1:N-1
    temp_1 = temp_1 + abs(v_smc(k+1,1)-v_smc(k,1));
    temp_2 = temp_2 + abs(v_smc(k+1,2)-v_smc(k,2));
end

temp_1 = temp_1/N;
fprintf("tvar_v_1 = %f\n", temp_1);
temp_2 = temp_2/N;
fprintf("tvar_v_2 = %f\n", temp_2);
