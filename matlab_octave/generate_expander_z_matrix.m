function [expander] = generate_expander_z_matrix(z, A)
   %% z: weight
   %% A: auxiliary matrix of compitability 
   expander = z .^ A;
   expander(find(A == -1)) = 0;
end 
