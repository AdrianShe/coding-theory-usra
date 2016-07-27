function [moments] = compute_moments_torus(z, A, C, num_its, normalize = false)
   %% z: weight
   %% A: an auxiliary matrix
   %% C: a counter
   [M, v] = generate_moment_matrix(z, A, C, false);
   num = zeros(3, length(C));

   for n=1:length(C) %% Complete torus state at a time
      init = cell(3,1);     
      for i=1:3
       init{i} = zeros(length(C), 1);
       init{i}(n) = v{i}(n);
      end

      for i=1:(num_its-1)
     		init{3} = M{3} * init{1} + M{2} * init{2} + M{1} * init{3}; %% Compute second moment
     		init{2} = M{2} * init{1} + M{1} * init{2}; %% Compute first moment 
     		init{1} = M{1} * init{1};
      end
      compat = find(A(n,:) != -1); 
      for i=1:3
         num(i,n) = sum(init{i}(compat));
      end
   end

   for i=1:3
     moments(i) = sum(num(i,:));
   end
   moments = moments';
end  
