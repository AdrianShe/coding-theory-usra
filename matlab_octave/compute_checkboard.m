function [ratio] = compute_checkboard(init, M, S, a, b, c, bottom, top, norm_factor = 1)
   %% init: initial vector of ones equal in length to rows(M)
   %% M: transfer matrix of height a+1
   %% S: list of sequences of length a+1
   %% a, b, c: lengths of sides (original height)
   %% bottom: pattern of sequences along bottom edge of length b+c
   %% top: pattern of sequences along top edge of length b+c
   
   %% Check for compitability with left edge and initial phase vectors
   pattern_left = bitshift(generate_pattern(a, top(1)), 1);
   matching = bitand(S, pattern_left);
   init(matching != 0) = 0;
   init = check_compats_b(init, S, top(1), bottom(1), a);
   
   %% Generate "b" portion
   for i=1:(b-1)
     init = (M * init) / norm_factor;
     init = check_compats_b(init, S, top(i + 1), bottom(i + 1), a);
   end 

   %% Change BCs at boundary
   res = (M * init) / norm_factor; 
   res_zero = res;
   res_zero(mod(S, 2) == 0) = 0;
   res = check_compats_c(res, S, top(b + 1), bottom(b + 1), a);
   res_zero = check_compats_c(res_zero, S, top(b + 1), bottom(b + 1), a);
  
   %% Generate "c" portion 
   for i=1:(c-1)
      res = (M * res) /norm_factor;
      res_zero = (M * res_zero) / norm_factor;
      res = check_compats_c(res, S, top(b+i+1), bottom(b+i+1), a);
      res_zero = check_compats_c(res_zero, S, top(b+i+1), bottom(b+i+1), a);
   end

   %% Check for compitability with right edge and return
   pattern_right = generate_pattern(a+1, top(b+c));
   matching = bitand(S, pattern_right);
   res(matching != 0) = 0;
  res_zero(matching != 0) = 0;
 sum(res)
   sum(res_zero)
   ratio = sum(res) / sum(res_zero);
end
