function [res] = implicit_2d_multiply(L,D,vec)
   %% Given an implicit representation of a matrix L
   %% where L indicates positions in matrix which == 1
   %% (and are 0 for all other positions), and D
   %% represents the unique elements in L
   res = zeros(length(vec),1);
   
   for i=1:rows(L)
       first = D(L(i,1) + 1); %% D is 1-indexed
       second = D(L(i,2) + 1);
       res(first) += vec(second);
   endfor
end
