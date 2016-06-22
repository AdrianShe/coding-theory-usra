function [M] = generate_z_matrix(z, A)
   %% Generate column-to-column transfer matrix
   %% weighting the presence of 1s
   %% z: weight
   %% A: auxiliary matrix of compitability 

   M = z .^ A;
end 
   
