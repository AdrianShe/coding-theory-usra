function [moments] = compute_moments(obj, weights, n)

  % norm_factor = obj{n-1}(1,idivide(3 * length(weights), 4));
  % temp(find(temp == Inf)) = 0;
  % norm_factor = max(temp);
  % for i=1:3
   % obj{n-1}(i,:) = obj{n-1}(i,:) / norm_factor;
   %end

   third = (weights .^ 3) * 6 * obj{n-1}(4,:); 
   second_moment = 2 * (weights .^ 2) .* obj{n-1}(3,:) + weights .* obj{n-1}(2,:);
   first_moment = weights .* obj{n-1}(2,:);
   third_moment = third + 3 * second_moment - 2 * first_moment;
 
   part = obj{n-1}(1,:) .^ 2;
   variance = ((obj{n-1}(1,:) .* second_moment) - (first_moment)) ./ part;
end