function [val] = brians_constant(T1, T2, E, init, b, c, norm_factor = 1)
   %% T1: transfer matrix for first section
   %% T2: transfer matrix for second section
   %% E: expander matrix between the two sections
   %% init: initial vector 
   %% b: the maximum value of b
   %% c: the maximum value of c
   %% norm_factor: normalization factor


   %% init = T2^(c-1) * E * T1^(b-1) * v
   %% init_zero = T2^(c-2) * E * T1^b * v
   top_b = max(b-1, 0);
   top_c = max(c-1, 0);
   bottom_b = max(b, 0);
   bottom_c = max(c-2, 0);
 
   init_top = T2 ^ top_c * E * T1 ^ top_b * init;
   if (c >= 2)
   	init_bottom = T2 ^ bottom_c * E * T1 ^ bottom_b * init;
   else
        init_bottom = T1 ^ bottom_b * init;
   end
   sum(init_top);
   sum(init_bottom);
   val = sum(init_top) / sum(init_bottom);
end
