function [S] = generate_sequences_numrep(n)
   %% Generates the list of binary strings
   %% of length n with no adjacent 1s 
   %% n: length of string
   
   %% Iterative method to generate all sequences
   all_sequences = cell(1, n + 1); %% Initialize array
   all_sequences{1} = 0;
   all_sequences{2} = [0 1];

   for i=3:(n+1) 
      sequences_zero = bitshift(all_sequences{i-1}, 1); %% Generate sequences ending in 0
      sequences_one = bitshift(all_sequences{i-2}, 2) + 1; %% Generate sequences ending in 1
      all_sequences{i} = [sequences_zero sequences_one]; %% Contacenate sequences
    endfor
 
   S = all_sequences{n + 1};
end 
