function [skewness] = compute_skewness(obj, weights, n)

  % norm_factor = obj{n-1}(1,idivide(3 * length(weights), 4));
  % temp(find(temp == Inf)) = 0;
  % norm_factor = max(temp);
  % for i=1:3
   % obj{n-1}(i,:) = obj{n-1}(i,:) / norm_factor;
   %end

   third = 6 * (weights .^ 3) .*  obj{n-1}(4,:); 
   second_moment = 2 * (weights .^ 2) .* obj{n-1}(3,:) + weights .* obj{n-1}(2,:);
   first_moment = weights .* obj{n-1}(2,:);
   third_moment = third + 3 * second_moment - 2 * first_moment;
    part = obj{n-1}(1,:);

   first_expect = first_moment ./ part;
   second_expect = second_moment ./ part;
   variance = second_expect - first_expect .^ 2;
   third_expect = third_moment ./ part;

   skewness = (third_expect - (3 * first_expect .* variance) - first_expect .^ 3) ./ (variance .^ (3/2));
end
