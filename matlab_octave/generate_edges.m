function [top, bottom] = generate_edges(a, b, c, p)
  top = zeros(1, b+c);
  bottom =  zeros(1, b+c);
  if (mod(a,2) == 0) %% Even means opposite phase
       top(1) = p;
       bottom(1) = !p; 
   else  %% Odd means same phase
       top(1) = p;
       bottom(1) = p;
   end
   
   %% Generate the rest of the pattern by alternating
   for i=2:b
      top(i) = !top(i-1);
      bottom(i) = !bottom(i-1);
   end
   
   %% Then expand and generate c
   top(b+1) = !top(b);
   bottom(b+1) = bottom(b);
  
   for i=(b+2):(b+c);
     top(i) = !top(i-1);
     bottom(i) = !bottom(i-1);
   end
end 
