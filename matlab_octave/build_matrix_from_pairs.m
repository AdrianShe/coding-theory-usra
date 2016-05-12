function [T] = build_matrix_from_pairs(L)
   %% Builds transfer matrix from a matrix of 
   %% compatible pairs L
 
   unique_seqs = unique(L);
   T = zeros(length(unique_seqs));

   for i=1:rows(L)
      first = find(unique_seqs == L(i,1));
      second = find(unique_seqs == L(i,2));
      T(first, second) = 1;
   endfor
end 
