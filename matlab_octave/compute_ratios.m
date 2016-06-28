function [ratios] = compute_ratios(res)
 ratios = zeros(size(res)(1) - 1, size(res)(2) - 1);
 for i=1:(size(res)(1) - 1)
   for j=2:size(res)(2)
     ratios(i, j-1) = (res(i, j) / res(i+1, j-1));
    end
  end
end 
