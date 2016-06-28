function [moments_ratio] = plot_moments(weights, obj, n)
 moments_ratio = (weights .* obj{n-1}(2,:)) ./ (n^2 * obj{n-1}(1,:));
end
