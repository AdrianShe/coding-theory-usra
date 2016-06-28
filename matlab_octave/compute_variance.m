function [variance] = compute_variance(obj, weights, n)
   second_moment = 2 * (weights .^ 2) .* obj{n-1}(3,:) + weights .* obj{n-1}(2,:);
   first_moment = (weights .* obj{n-1}(2,:)) .^ 2;
   part = obj{n-1}(1,:) .^ 2;
   variance = ((obj{n-1}(1,:) .* second_moment) - (first_moment)) ./ part;
end
