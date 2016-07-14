function [results] = compute_checkboard_main(a, b, c, z)
   %% Compute checkboard ratios
   %% a: size of left edge (fixed)
   %% b: lengths of left edge
   %% c: lengths of right edge
   %% z: weights

   results = cell(length(a), length(z));
   
   for l=1:length(a)
   S = generate_sequences_numrep(a(l)+1);
   C = counter(S); 
   A = generate_auxiliary_matrix(S, C, S, C);
   init = ones(length(S), 1);
 
   for i=1:length(z)
         matrix = zeros(length(b), length(c));
         M = generate_z_matrix(z(i), A);
       
 	 for j=1:length(b)
            for k=1:length(c)
                  [top, bottom] = generate_edges(a(l), b(j), c(k));
                   
                  if (z(i) >= 2)
 		    matrix(j, k) = compute_checkboard(init, M, S, a(l), b(j), c(k), bottom, top, z(i)^max(C));
                  else 
        	    matrix(j, k) = compute_checkboard(init, M, S, a(l), b(j), c(k), bottom, top);
                  end

                  printf('%d %d %d %f \n', a(l), b(j), c(k), z(i)); fflush(stdout);     
            end
         end 
         results{l, i} = matrix;
   end
  end
end
