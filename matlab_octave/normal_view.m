function [extracted] = normal_view(obj, weights, a, b, c)
 %% Give a normal view as in the other function
 extracted = zeros(3, length(weights)); 
 
 for i=1:length(weights)
   extracted(1,i) = obj{a-1, i, 1}(b, c); 
   extracted(2,i) = obj{a-1, i, 2}(b, c); 
   extracted(3,i) = obj{a-1, i, 3}(b, c); 
 end
end
