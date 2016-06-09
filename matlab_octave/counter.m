function [C] = counter(L)
   %% Returns the number of 1s in each element of L
   %% L: input list of sequences

   C = zeros(1, length(L));
   for i=1:length(L) 
     string = dec2bin(L(i));
     C(i) = length(find(string == '1'));
   endfor
end
