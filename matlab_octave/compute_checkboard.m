function [res] = compute_checkboard(init, M, b, E, L, c)
   %% init: initial vector
   %% M: multiply out the b side, b: length
   %% E: expander
   %% L: multiply out the c side, c: length
   %% last: final column matrix
  for i=1:(b-1)
    if (mod(i, 2) == 0)
         init = M * init;
    else
         init = M' * init;
    end
  end
  
  init = E * init;    

  for i=1:(c-1)
     if (mod(i,2) == 0)
        init = L * init;
     else
        init = L' * init;
     end
   end
  res = init;
end
