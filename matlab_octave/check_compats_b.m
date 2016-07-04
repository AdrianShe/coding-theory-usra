function [compat] = check_compats_b(vec, S, t, b, a)
   %% Check for compatibilities 
   compat = vec;
   compat(mod(S, 2) == !b) = 0; %% Force bottom to match
   if (t == 1)
      compat(S >= 2^a) = 0; %% Force top to match
   end
end
