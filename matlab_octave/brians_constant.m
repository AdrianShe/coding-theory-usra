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
   for i=1:(b-1)
      init = (T1 * init) / norm_factor; 
   end
   init_zero = T1 * init / norm_factor;

   %% Now expand
   init = E * init/ norm_factor;
   init_zero = E * init_zero / norm_factor;

   %% Now complete the second part
   for i=1:(c-2)
      init = T2 * init / norm_factor;
      init_zero = T2 * init_zero /norm_factor;
   end
   init = T2 * init / norm_factor;
   sum(init)
   sum(init_zero)
   val = sum(init) / sum(init_zero);
end
