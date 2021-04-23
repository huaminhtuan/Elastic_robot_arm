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
function [theta_d] = lqr(e, edot, q, qdot, theta, thetadot, theta_dk_1, qddot, qddotdot, prevW)
    assert(isa(e,'double') && isa(edot,'double') && isa(q,'double') && isa(qdot,'double')...
       && isa(theta,'double') && isa(thetadot,'double') && isa(qddot,'double') && isa(qddotdot,'double') && isa(prevW,'double'));
    assert(isa(theta_dk_1,'double'));
%%%%%%%%%% Local variable %%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%% Control variable %%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%% Control signal %%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

