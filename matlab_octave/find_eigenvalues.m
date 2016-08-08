ring_eigvals = zeros(15, 2001);
for i=1:15
   S = generate_ring_sequences_numrep(i);
   C = counter(S);
   A = generate_auxiliary_matrix(S, C, S, C);
   z = 2 .^ [-10:0.01:10];
   for j=1:length(z)
    M = generate_z_matrix(z(j), A);
    ring_eigvals(i, j) = max(eigs(M));
    fprintf('%f %d \n', z(j), i)
    fflush(stdout);
   end
end
