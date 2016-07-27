function [moments] = compute_checkboard_square_moments(a, num_its, S, M, v, top, bottom, left, right)
  %% a: height
  %% b: number of iterations
  %% S: sequences of length a
  %% M, v: moment vectors nad matrices
  %% top, bottom, left, right: top/left/bottom/right sequences

  idx = find(bitand(S, left) != 0); %% find incompitable left ones
  for i=1:3
    v{i}(idx) = 0;
    v{i} = check_compats_c(v{i}, S, top(1), bottom(1), a-1);
  end
 
  %% Compute middle moments checking for compitability
  for i=1:(num_its-1)
     v{3} = M{3} * v{1} + M{2} * v{2} + M{1} * v{3}; %% Compute second moment
     v{2} = M{2} * v{1} + M{1} * v{2}; %% Compute first moment 
     v{1} = M{1} * v{1};
     for j=1:3
       v{j} = check_compats_c(v{j}, S, top(i+1), bottom(i+1), a-1);
     end
   end
  
   idx = find(bitand(S, right) != 0); %% find incompitable right ones
   for i=1:3
    v{i}(idx) = 0;
   end
  
   moments = zeros(3,1); %% complete the moments
   for i=1:3
     moments(i) = sum(v{i});
   end
end 
