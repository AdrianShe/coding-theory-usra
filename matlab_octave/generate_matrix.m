function [M] = generate_matrix(n)
   %% Generates the transfer matrix for a system
   %% of height n 
    
   S = generate_sequences(n);
   size_of_matrix = rows(S);
   M = zeros(size_of_matrix);
   for i=1:size_of_matrix
      for j=i:size_of_matrix
          ortho = S(i,:) * S(j,:)'; %% Each row is a code
          if ortho == 0 %% If the bit strings multiply out to 1, then the corresponding
          %% entry in the transfer matrix should be zero.
             M(i,j) = 1;
             M(j,i) = 1;
          endif
      endfor
   endfor 
end
