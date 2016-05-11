function [all_pairs] = all_pairs_numrep(n)
   %% Generates the all pairs of binary strings
   %% of length n with no adjacent 1s 
   %% n: length of string
   
   %% Iterative method to generate all sequences
   all_sequences = cell(1, n + 1); %% Initialize array
   all_sequences{1} = {[0 0]};
   all_sequences{2} = {[0 0], [0 1], [1 0]};

   %% Position 0 ends in 0 0, Position 1 ends in 0 1, 
   %% Position 1 ends in 1 0
   for i=3:(n+1)
      seq = all_sequences{i-1};
      seq_zero_zero = bitshift(seq{1}, 1);
      seq_zero_one = bitshift(seq{2}, 1);
      seq_one_zero = bitshift(seq{3}, 1);
     
     %% Form sequences ending in 0, 1 from 1st and 3rd columns
      all_seq_zero_one = [[seq_zero_zero(:,1) seq_zero_zero(:,2) + 1];
 [seq_one_zero(:,1) seq_one_zero(:,2) + 1]];
      
     %% Form sequences ending in 1, 0 from 1st and 2nd columns
     all_seq_one_zero = [[seq_zero_zero(:,1) + 1 seq_zero_zero(:,2)];
[seq_zero_one(:,1) + 1 seq_zero_one(:,2)]];
 
     %% Form sequences from 0,0 by contacenating all columns
     all_seq_zero_zero = [seq_zero_zero; seq_zero_one; seq_one_zero];

     all_sequences{i} = {all_seq_zero_zero, all_seq_zero_one, all_seq_one_zero};      
   endfor

  % for i=3:(n+1) 
   %   sequences_zero = bitshift(all_sequences{i-1}, 1); %% Generate sequences ending in 0
    %  sequences_one = bitshift(all_sequences{i-2}, 2) + 1; %% Generate sequences ending in 1
     % all_sequences{i} = [sequences_zero sequences_one]; %% Contacenate sequences
    %endfor
   seq = all_sequences{n+1};
   all_pairs = [];
   for i=1:length(seq) 
       all_pairs = [all_pairs; seq{i}];
   endfor 
end 
