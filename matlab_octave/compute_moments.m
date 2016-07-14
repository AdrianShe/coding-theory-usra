function [moments] = compute_moments(z, A, C, num_its, third_moment = false, normalize = false)
   %% z: weight
   %% A: an auxiliary matrix
   %% C: a counter
   [M, v] = generate_moment_matrix(z, A, C, third_moment);
   
   if (normalize)
   norm_factor = max(C);
   for i=1:3
     v{i} = v{i} / (z ^ norm_factor);
   end
   end
 
   if (normalize & third_moment)
     v{4} = v{4} / (z ^ norm_factor);
   end
   
   for i=1:(num_its-1)
     if (third_moment)
        v{4} = M{4} * v{1} + M{3} * v{2} + M{2} * v{3} + M{1} * v{4};
     end
     v{3} = M{3} * v{1} + M{2} * v{2} + M{1} * v{3}; %% Compute second moment
     v{2} = M{2} * v{1} + M{1} * v{2}; %% Compute first moment 
     v{1} = M{1} * v{1};
   end

   for i=1:3
     moments(i) = sum(v{i});
   end

   if (third_moment)
     moments(4) = sum(v{4});
   end
   moments = moments';
end  
