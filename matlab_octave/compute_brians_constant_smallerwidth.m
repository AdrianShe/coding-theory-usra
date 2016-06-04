probabilities = reshape(1:500, 20, 5, 5);

for a=1:20
   T1 = generate_matrix_numrep(a);
   T2 = generate_matrix_numrep(a+1);
   E = generate_expander_matrix(a);
   printf('Finishing generating matrix \n');
   fflush(stdout);
   vals = compute_all_constants(T1, T2, E, a, 5, 6);
   probabilities(a,:,:) = vals;
endfor
