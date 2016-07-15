free_results = cell(3,1);

for a=13:15
   seq = generate_sequences_numrep(a);
   seq2 = generate_sequences_numrep(a+1);
   C = counter(seq);
   D = counter(seq2);
   A = generate_auxiliary_matrix(seq, C, seq, C);
   B = generate_auxiliary_matrix(seq2, D, seq2, D);
   E = generate_auxiliary_matrix(seq, C, seq2, D); 
   A = generate_z_matrix(10, A);
   B = generate_z_matrix(10, B);
   E = generate_z_matrix(10, E);   
   printf('Finishing generating matrix \n');
   fflush(stdout);

   vals = zeros(21, 21);
   init = 10 .^ (C'); 

   for i=20:40
    for j=20:40
        fprintf('%d %d %d \n', a, i, j); 
   	vals(i-19, j-19) = brians_constant(A, B, E, init , i, j, 10 ^ max(C));
        fflush(stdout);
    end
   end
   free_results{a-12} = vals;
end
