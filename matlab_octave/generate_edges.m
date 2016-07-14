function [top, bottom] = generate_edges(a, b, c)
  top = zeros(1, b+c);
  bottom =  zeros(1, b+c);
  bottom(b) = 0; %% Set bottom phase
  bottom(b+1) = 0; 

  for i=(b-1):-1:1
    bottom(i) = !bottom(i+1);
  end
  for i=(b+2):(b+c)
    bottom(i) = !bottom(i-1); 
  end

  if (mod(a,2) == 0) %% Even means opposite phase
       top(1) = !bottom(1);
   else  %% Odd means same phase
       top(1) = bottom(1);
   end
   
   %% Generate the rest of the pattern by alternating the top
   for i=2:(b+c)
      top(i) = !top(i-1);
   end
end 
