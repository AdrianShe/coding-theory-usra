function [moments] = compute_moments(z, A, C, num_its)
   %% z: weight
   %% A: an auxiliary matrix
   %% C: a counter
   [M, v] = generate_moment_matrix(z, A, C);
   
   for i=1:(num_its-1)
     v{3} = M{3} * v{1} + M{2} * v{2} + M{1} * v{3}; %% Compute second moment
     v{2} = M{2} * v{1} + M{1} * v{2}; %% Compute first moment 
     v{1} = M{1} * v{1};
   end

   for i=1:3
     moments(i) = sum(v{i});
   end
   moments = moments';
end  
