probabilities = reshape(1:8000, 5, 40, 40);

for a=15:20
   T1 = generate_matrix_numrep(a);
   T2 = generate_matrix_numrep(a+1);
   E = generate_expander_matrix(a);
   printf('Finishing generating matrix \n');
   fflush(stdout);
   vals = compute_all_constants(T1, T2, E, a, 40, 41);
   probabilities(a - 14,:,:) = vals;
endfor
