function [moments_ratio] = density(obj, weights, n)
 moments_ratio = (weights .* obj{n-1}(2,:)) ./ (obj{n-1}(1,:));
end
