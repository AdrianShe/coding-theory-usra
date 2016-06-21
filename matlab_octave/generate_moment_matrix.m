function [M, v] = generate_moment_matrix(z, S, C)
   %% Generate column-to-column transfer matrix
   %% weighting the presence of 1s
   %% z: weight
   %% S: collection of sequences
   %% C: counter object for S
   %% M: cell array with original matrix, and first/second moments
   %% v: cell array with initial states for vector v

   %% Intiialize table of powers of z
   z_table = zeros(max(C) + 1, 1);
   for i=1:length(z_table)
      z_table(i) = z^(i-1);
   endfor
      
   M = cell(3,1);
   v = cell(3,1);

   for i=1:3
      M{i} = zeros(length(C));
      v{i} = zeros(length(C), 1);
   endfor 

   %% Generate matricies. 
   for i=1:length(S)
    for j=i:length(S)
      if (bitand(S(i), S(j)) == 0)
        M{1}(i,j) = z_table(C(i) + 1); %% Generate original matrix
        M{1}(j,i) = z_table(C(j) + 1);

        if (C(i) >= 1) %% Generate matricies for moments
            M{2}(i,j) = C(i) * z_table(C(i));
            if (C(i) >= 2)
              M{3}(i,j) = nchoosek(C(i), 2) * z_table(C(i) - 1);
            endif
        endif
        
        if (C(j) >= 1)
            M{2}(j,i) = C(j) * z_table(C(j));
            if (C(j) >= 2)
              M{3}(j,i) = nchoosek(C(j), 2) * z_table(C(j) - 1);
            endif
        endif
      endif
     endfor
   endfor
   
  %% Generate initial vectors
  v{1} = z .^ C'; %% Zeroth moment vector 
  
  F = C' - 1;
  F(find(F == -1)) = 0;
  v{2} = C' .* (z .^ F); %% n * z^(n-1): first moment vector
 
  S = F - 1;
  S(find(S == -1)) = 0;
  v{3} = ((C' .* F) ./ 2) .* (z .^ S); %% n(n-1)/2 * z^(n-2): second moment
end 
   
