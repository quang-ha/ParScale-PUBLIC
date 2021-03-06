function [omega_v,time] = Wen_omega_v (xi_m,ThieleMod,D_ratio,N_sh,C_A0,k_v)
%Function to calculate the dimensionless time fot second stage reaction
% for a given reaction front position
%Formulars according Wen, "Noncatalytic Heterogenous Solid Fluid Reaction Models"
%models p. 43, eqn. 39
% Copyright: Stefan Radl / Thomas Forgber, IPPT, TU Graz
% INPUT
%   xi_m      ... dimensionless radius of reaction front
%   TODOs (specify all input)
% OUTPUT
%   TODOs (specify all output)

    xi_m = max(1e-6, xi_m); %bound to avoid abuse and problem with function inversion
    xi_m = min(1.0, xi_m);  %bound to avoid abuse and problem with function inversion

    if(ThieleMod<700)
        sinhTerm =  xi_m ...
                 .* sinh(ThieleMod) ...
                 ./ sinh(ThieleMod.*xi_m) ;
    else
        error('This function cannot be evaluated for Thiele Moduli > 700')
    end

    cothTerm = ( ...
                          ThieleMod.*xi_m ...
                  .* coth(ThieleMod.*xi_m) ...
                  -  1 ...
               );

    omega_v =  1  ...
            + (1 - D_ratio)  ...
              .* log(sinhTerm)...
            + ThieleMod.*ThieleMod ./ 6.0 ...
               .* (1-xi_m).*(1-xi_m) ...
               .* (1+2.*xi_m)...
               ...
            + D_ratio ...
              .*(1-xi_m)...
              .*cothTerm ...
                ...
            + ThieleMod.*ThieleMod...
               ./(3.*N_sh) ...
               .*(1-xi_m.*xi_m.*xi_m)...
               ...
            + xi_m ...
               ./N_sh...
               .*cothTerm;
               
    time = omega_v ./ (C_A0 .* k_v);
end
