function [moments] = compute_moments_l(M, E, N, b, c, v)
   %% M: matrix for smaller size
   %% E: expander matrix
   %% N :matrix for larger size
   %% b, c: lengths
   %% v: initial vectors
  
   
   for i=1:(b-1)
     v{3} = M{3} * v{1} + M{2} * v{2} + M{1} * v{3}; %% Compute second moment
     v{2} = M{2} * v{1} + M{1} * v{2}; %% Compute first moment 
     v{1} = M{1} * v{1};
   end
 
   %% Expand the matrix
     v{3} = E{3} * v{1} + E{2} * v{2} + E{1} * v{3}; %% Compute second moment
     v{2} = E{2} * v{1} + E{1} * v{2}; %% Compute first moment 
     v{1} = E{1} * v{1};

   for i=1:(c-1)
     v{3} = N{3} * v{1} + N{2} * v{2} + N{1} * v{3}; %% Compute second moment
     v{2} = N{2} * v{1} + N{1} * v{2}; %% Compute first moment 
     v{1} = N{1} * v{1};
   end
 
   for i=1:3
     moments(i) = sum(v{i});
   end
   moments = moments';
end  
