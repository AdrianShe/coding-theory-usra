function [expander] = generate_expander_matrix(a)
   %% a: original size
   sequences_a = generate_sequences_numrep(a);
   sequences_expanded = generate_sequences_numrep(a+1);
   shifted = bitshift(sequences_a, 1);

   expander = zeros(length(sequences_expanded), length(shifted));

   for i=1:length(shifted)
      result = bitand(shifted(i), sequences_expanded);
      result = (result ==  0);
      expander(:,i) = result;
   endfor  
end 
