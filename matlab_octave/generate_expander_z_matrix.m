function [expander] = generate_expander_z_matrix(z, S, E, C)
   %% z: weight
   %% S: shifted original sequences of length a
   %% E: expanded sequences of length a+1
   %% C: counter object for E
   expander = zeros(length(E), length(S));
 
   powers = zeros(max(C) + 1, 1);
   for i=1:length(powers)
       powers(i) = z^(i-1);
   endfor

   for i=1:length(S)
      result = bitand(S(i), E);
      result = (result ==  0);
      for j=1:length(result)
         if result(j) == 1 
             expander(j,i) = powers(C(j) + 1);
         endif
      endfor 
   endfor  
end 
