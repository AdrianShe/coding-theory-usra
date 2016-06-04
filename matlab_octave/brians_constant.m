function [val] = brians_constant(T1, T2, E, a, b, c)
   %% b: the maximum value of b
   %% c: the maximum value of c
   number_bottom = T2^(c-1) * E * T1^(b-1) * ones(rows(T1), 1);
   number_top = T2^(c-2) * E * T1^b * ones(rows(T1), 1);
   val = sum(number_top) / sum(number_bottom);
end
