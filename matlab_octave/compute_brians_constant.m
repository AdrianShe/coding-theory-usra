free_results = cell(10,1);

for a=1:10
   seq = generate_sequences_numrep(a);
   seq2 = generate_sequences_numrep(a+1);
   C = counter(seq);
   D = counter(seq2);
   A = generate_auxiliary_matrix(seq, C, seq, C);
   B = generate_auxiliary_matrix(seq2, D, seq2, D);
   E = generate_auxiliary_matrix(seq, C, seq2, D); 
   A = generate_z_matrix(1, A);
   B = generate_z_matrix(1, B);
   E = generate_z_matrix(1, E);   
   printf('Finishing generating matrix \n');
   fflush(stdout);

   vals = zeros(20, 20);
   init = ones(length(C), 1); 

   for i=1:20
    for j=1:20
        fprintf('%d %d %d \n', a, i, j); 
   	vals(i, j) = brians_constant(A, B, E, init , i, j);
        fflush(stdout);
    end
   end
   free_results{a} = vals;
end
