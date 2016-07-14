function [variance] = variance(obj, weights, n)
   second_moment = 2 * (weights .^ 2) .* obj{n}(3,:) + weights .* obj{n}(2,:);
   first_moment = (weights .* obj{n}(2,:)) .^ 2;
   part = obj{n}(1,:) .^ 2;
   variance = ((obj{n}(1,:) .* second_moment) - (first_moment)) ./ part;
end
