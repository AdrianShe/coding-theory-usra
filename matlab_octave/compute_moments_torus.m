function [moments] = compute_moments_torus(z, A, C, num_its, normalize = false)
   %% z: weight
   %% A: an auxiliary matrix
   %% C: a counter
   [M, v] = generate_moment_matrix(z, A, C, false);
   num = zeros(1, length(C));

   for n=1:length(C) %% Complete torus state at a time
      init = zeros(length(C), 1);
      init(n) = v{1}(n); 
     
    
      for i=1:(num_its-1)
%     		init{3} = M{3} * init{1} + M{2} * init{2} + M{1} * init{3}; %% Compute second moment
 %    		init{2} = M{2} * init{1} + M{1} * init{2}; %% Compute first moment 
     		init = M{1} * init;
      end
      compat = find(A(n,:) != -1); %% Find last ones which are compat with first
      num(n) = sum(init(compat));
      fprintf('%d %f \n', C(n), num(n));
      fflush(stdout);
   end

  % for i=1:3
  %   moments(i) = sum(num(i,:));
  % end
   moments = sum(num);
end  
