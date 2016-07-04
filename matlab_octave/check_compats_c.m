function [compat] = check_compats_c(vec, S, t, b, a)
   %% Check for compatibilities 
   compat = vec;
   if (b == 1) 
      compat(mod(S, 2) == 1) = 0; %% Make sure bottom matches
   end
   if (t == 1)
      compat(S >= 2^a) = 0; %% Make sure top matches
   end
end
