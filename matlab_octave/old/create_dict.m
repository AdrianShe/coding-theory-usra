function [dict] = create_dict(D)
   %% Create dictionary of allowed words 
   %% Look up position
   %% Eg. if D = [0 2 1 4 5]
   %% Then D is of length max(D) + 1 and contains position
   %% dict = [1 3 2 0 4 5]
   
   dict = zeros(1, max(D) + 1);
   
   for i=0:max(D)
       idx = find(D == i);
       if (columns(idx) == 0)
          dict(i+1) = 0;
       else  
          dict(i+1) = idx;
       endif
   endfor             
end 
    
