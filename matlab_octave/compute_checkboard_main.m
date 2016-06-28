function [matrix] = compute_checkboard_main(n, b, c)
   generate_checkboard_initialize;
   res = zeros(length(b), length(c));
   
   for i=1:length(b)
    for j=1:length(c)

      if (mod(b(i), 2) == 0 && mod(c(j), 2) == 0)
          vec = compute_checkboard(first, M, b(i), one_zero_expander_matrix, L, c(j));
          vec(zero_right_indexes_zero) = 0;
          matrix(i,j) = sum(vec); 
      end
 
      if (mod(b(i), 2) == 1 && mod(c(j), 2) == 0)
          vec = compute_checkboard(first, M, b(i), zero_one_expander_matrix, L', c(j)); 
          vec(zero_right_indexes_one) = 0;
          matrix(i,j) = sum(vec); 
      end

      if (mod(b(i), 2) == 0 && mod(c(j), 2) == 1)
          vec = compute_checkboard(first, M, b(i), one_zero_expander_matrix, L, c(j)); 
          vec(zero_right_indexes_one) = 0;
          matrix(i,j) = sum(vec); 
      end

      if (mod(b(i), 2) == 1 && mod(c(j), 2) == 1)
          vec = compute_checkboard(first, M, b(i), zero_one_expander_matrix, L', c(j)); 
          vec(zero_right_indexes_zero) = 0;
          matrix(i,j) = sum(vec); 
      end
     end
   end
end
