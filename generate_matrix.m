%% TODO: Exploit symmetry of matrix M
function [M] = generate_matrix(n)
   %% Generates the transfer matrix for a system
   %% of height n 
    
   S = generate_sequences(n);
   size_of_matrix = rows(S);
   M = ones(size_of_matrix);
   for i=1:size_of_matrix
      for j=1:size_of_matrix
          ortho = S(i,:) * S(j,:)'; %% Each row is a code
          if ortho >= 1 %% If the bit strings multiply out to 1, then the corresponding
          %% entry in the transfer matrix should be zero.
             M(i,j) = 0;
          endif
      endfor
   endfor 
end
