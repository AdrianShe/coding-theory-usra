function [values] = extract_values(obj,a,b,c)
    for i=1:size(obj)(2)
      values(i) = obj{a,i}(b,c-1);
    end
end
