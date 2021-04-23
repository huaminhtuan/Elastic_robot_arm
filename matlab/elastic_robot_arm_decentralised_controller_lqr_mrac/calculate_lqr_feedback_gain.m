Ks = 1400; % Spring stiffness 
Ds = 0.1; % Spring damping coefficient
Jl = 0.1; % Load inertia
Dl = 0.2; % Load damping coefficient
N = 10; % Gear ratio

A = [-Ks/Jl    -(Ds+Dl)/Jl];
B = Ks*(N^(-1));
C = 1;