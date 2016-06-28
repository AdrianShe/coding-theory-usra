function [A] = generate_auxiliary_matrix(S, C, T, D)
   %% Generate column-to-column transfer matrix
   %% weighting the presence of 1s
   %% S: collection of sequences
   %% C: counter object for S
   %% T: collection of sequences
   %% D: counter object for S

   A = zeros(length(T), length(S));
   if (length(S) == length(T)) %% Symmetric Case
      for i=1:length(S)
        for j=i:length(T)
         if (bitand(S(i), T(j)) == 0)
                A(i,j) = C(i);
                A(j,i) = C(j);
        end
       end
   
   else %% Non-symmetric case
        for i=1:length(T)
           for j=1:length(S)
               if (bitand(T(i), S(j)) == 0)
                  A(i,j) = D(i);
               else
                  A(i,j) = -Inf;
               end
            end
         end
   end
end 
