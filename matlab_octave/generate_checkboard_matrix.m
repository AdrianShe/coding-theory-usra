function [M] = generate_checkboard_matrix(S, from_compat, end_compat)
   %% Generate a checkboard matrix for phase transition from p to !p
   %% compatiability vector 
   M = zeros(length(S)); 
   
   for i=1:length(S)
      if (end_compat(i) == 1) %% Only do something if to is compitable 
          all_compat = !bitand(S(i), S); %% Check compitability (as regular)
          all_compat(find(from_compat == 0)) = 0;%% Zero out from compitabilities 
          M(i,:) = all_compat;
      end
   end    
end
