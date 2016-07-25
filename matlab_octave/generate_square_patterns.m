function [top, bottom, left, right] = generate_square_patterns(a,b,p)
     left = generate_pattern(a, p);
     top = zeros(1, b);
     top(1) = p;
     for i=2:b
        top(i) = !top(i-1);
     end

     if (mod(a,2) == 0)
    	bottom = !top;
     else
   	bottom = top;
     end
  
    right = generate_pattern(a, top(b));
end
