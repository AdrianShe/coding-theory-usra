weights = [-1:0.1:10];
weights = 2 .^ weights
probabilities = cell([10 length(weights)]);

for a=1:10
   S = generate_sequences_numrep(a);
   C = counter(S);
   Sh = bitshift(S, 1);
   L = generate_sequences_numrep(a+1);
   Cl = counter(L);
   for z = 1:length(weights)
        weight = weights(z);
        T1 = generate_z_matrix(weight, S, C);
        T2 = generate_z_matrix(weight, L, Cl);
        E = generate_expander_z_matrix(weight, Sh, L, Cl);
        printf('Finishing generating matrix %d \n', weight);
        fflush(stdout);
        vals = compute_all_constants(T1, T2, E, a, 15, 15);
        probabilities{a, z} = vals;
   end
end
save results_brian_weighted_finer.txt probabilities

