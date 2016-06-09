function [M] = generate_z_matrix(z, S, C)
   %% Generate column-to-column transfer matrix
   %% weighting the presence of 1s
   %% z: weight
   %% S: collection of sequences
   %% C: counter object for S

   z_table = zeros(max(C) + 1, 1);
   for i=1:length(z_table)
      z_table(i) = z^(i-1);
   endfor
      
   M = zeros(length(S));
   for i=1:length(S)
    for j=i:length(S)
      if (bitand(S(i), S(j)) == 0)
        M(i,j) = z_table(C(i) + 1);
        M(j,i) = z_table(C(j) + 1);
      endif
     endfor
   endfor
end 
   
