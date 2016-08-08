function [results] = compute_triangle_main(a, z)
   %% Compute triangle ratios
   %% a: size of left edge (fixed)
   %% z: weights

   results = zeros(length(a), length(z));
   
   for l=1:length(a)
    S = generate_sequences_numrep(a(l)+1);
    C = counter(S); 
    A = generate_auxiliary_matrix(S, C, S, C);
           heights = [1:a(l) a(l):-1:1]

   for i=1:length(z)
         M = generate_z_matrix(z(i), A);
         init = z(i) .^ C'; 
         results(l,i) = compute_triangle(init, M, S, a(l), heights);
         fprintf('%d %d', a(l), z(i)); fflush(stdout); 
   end
  end
end