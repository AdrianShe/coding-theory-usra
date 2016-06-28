function [data] = extract_matrix(obj, a, b, c)
   %% a: fixed a
   s = size(obj)(2);
   if (length(b) == 1)
      data = zeros(length(c), s);
      for i=1:length(c)
        data(i,:) = extract_values(obj, a, b, c(i));
      end
   end

   if (length(c) == 1)
      data = zeros(length(b), s);
      for i=1:length(b)
         data(i,:) = extract_values(obj, a, b(i), c);
      end
   end
end
