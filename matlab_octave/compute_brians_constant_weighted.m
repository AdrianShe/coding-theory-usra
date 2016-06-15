weights = [-1:0.01:10];
weights = 2 .^ weights;
probabilities = cell([15 length(weights)]);

for a=1:15
   S = generate_sequences_numrep(a);
   C = counter(S);
   Sh = bitshift(S, 1);
   L = generate_sequences_numrep(a+1);
   Cl = counter(L);
   for z = 1:length(weights)
	ones_vector = zeros(length(C), 1);
        weight = weights(z);
	for i = 1:length(C)
            ones_vector(i) = weight ^ C(i);
	endfor
	ones_vector
        T1 = generate_z_matrix(weight, S, C);
        T2 = generate_z_matrix(weight, L, Cl);
        E = generate_expander_z_matrix(weight, Sh, L, Cl);
        printf('Finishing generating matrix %d \n', weight);
        fflush(stdout);
        vals = compute_all_constants(T1, T2, E, a, 40, 40, ones_vector);
        probabilities{a, z} = vals;
   end
end
save results_brian_weighted_finer.txt probabilities

