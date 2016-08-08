function [ratio] = compute_triangle(init, M, S, a, height, norm_factor = 1)
   %% init: initial vector of ones equal in length to rows(M)
   %% M: transfer matrix of height a+1
   %% S: list of sequences of length a+1
   %% a: size of triangle
   %% height: list of heights
   
   init(S >= 4) = 0;
   
   %% Generate "b" portion
   for i=1:(a-1)
     init = (M * init) / norm_factor;
     init(mod(S, 2) == 1) = 0;
     init(S >= 2^(height(i+1) + 1)) = 0;
   end 

   %% Change BCs at boundary
   res = (M * init) / norm_factor; 
   res(S >= 2^(height(a+1))) = 0;
   res_zero = res;
   res_zero(mod(S, 2) == 1) = 0;
   
   %% Generate "c" portion 
   for i=1:(a-1)
      res = (M * res) /norm_factor;
      res_zero = (M * res_zero) / norm_factor;
      res(S >= 2^(height(a+i+1))) = 0;
      res_zero(S >= 2^(height(a+i+1))) = 0;
   end
   
   sum(res)
   sum(res_zero)
   ratio = sum(res) / sum(res_zero);
end
