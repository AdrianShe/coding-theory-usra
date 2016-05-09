function [S] = generate_sequences(n)
   %% Generates the list of binary strings
   %% of length n with no adjacent 1s 
   %% n: length of string
   
   %% Iterative method to generate all sequences
   all_sequences = cell(1, n + 1); %% Initialize array
   all_sequences{1} = zeros(1,0);
   all_sequences{2} = [0; 1];

   for i=3:(n+1)
      rows_zeros = rows(all_sequences{i-1});
      rows_ones = rows(all_sequences{i-2});
      sequences_zero = [all_sequences{i-1} zeros(rows_zeros, 1)]; %% Generate sequences ending in 0
      sequences_one = [all_sequences{i-2} zeros(rows_ones, 1) ones(rows_ones, 1)]; %% Generate sequences ending in 1
      all_sequences{i} = [sequences_zero; sequences_one]; %% Contacenate sequences
    endfor

   rows(all_sequences{n+1}); %% Display number of sequences, sanity check.
   S = all_sequences{n + 1};
end 
