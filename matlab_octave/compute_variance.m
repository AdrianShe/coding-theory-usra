function [variance] = compute_variance(obj, weights, i)
   second_moment = 2 * (weights .^ 2) .* obj{i}(3,:) + weights .* obj{i}(2,:);
   first_moment = (weights .* obj{i}(2,:)) .^ 2;
   part = obj{i}(1,:) .^ 2;
   variance = ((obj{i}(1,:) .* second_moment) - (first_moment)) ./ part;
end
