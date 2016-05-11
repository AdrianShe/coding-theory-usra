function [M] = generate_matrix_numrep(n)
   %% Generates the transfer matrix for a system
   %% of height n 
    
   S = generate_sequences_numrep(n);
   size_of_matrix = length(S);
   M = zeros(size_of_matrix); 
   for i=1:size_of_matrix
      for j=i:size_of_matrix        
          if bitand(S(i), S(j)) == 0 %% If the bit strings multiply out to 0, then they are compiatble
          %% entries in the transfer matrix should be zero.
             M(i,j) = 1;
             M(j,i) = 1;
          endif
      endfor
   endfor 
end
