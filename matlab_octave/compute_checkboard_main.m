function [matrix] = compute_checkboard_main(a, b, c, z, p)
   %% Compute checkboard ratios
   %% a: size of left edge (fixed)
   %% b: lengths of left edge
   %% c: lengths of right edge
   %% z: weights
   %% p: initial phase 

   results = cell(length(z), 1); 
   S = generate_sequences_numrep(a+1);
   C = counter(S); 
   A = generate_auxiliary_matrix(S, C, S, C);
   init = ones(length(S), 1);    
   for i=1:length(z)
         matrix = zeros(length(b), length(c));
         M = generate_z_matrix(z(i), A); 
         
 	 for j=1:length(b)
            for k=1:length(c)
                  [top, bottom] = generate_edges(a, b(j), c(k), p);
 		  matrix(j, k) = compute_checkboard(init, M, S, a, b(j), c(k), bottom, top); 
                  printf('%d %d %d %f \n', a, b(j), c(k), z(i)); fflush(stdout);
            end
         end 
        results{i} = matrix;
   end
end
