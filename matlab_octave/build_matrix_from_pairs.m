function [T] = build_matrix_from_pairs(L)
   %% Builds transfer matrix from a matrix of 
   %% compatible pairs L
 
   unique_seqs = unique(L);
   dict = create_dict(unique_seqs');
   T = zeros(length(unique_seqs));

   for i=1:rows(L)
      first = dict(L(i,1) + 1);
      second = dict(L(i,2) + 1);
      T(first, second) = 1;
   endfor
end 
