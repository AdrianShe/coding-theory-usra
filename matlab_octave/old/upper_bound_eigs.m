upper_bound_eigs = zeros(1, 20)

for i=1:20
   T = generate_ring_matrix_numrep(i);
   upper_bound_eigs(i) = explicit_power(T, eps, ones(rows(T), 1));
   printf('Done %d \n', i);
  % fflush(stdout);
endfor
