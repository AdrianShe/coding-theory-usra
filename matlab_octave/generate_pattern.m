function [hidden] = generate_pattern(n, p)
%% Generates vector of 1s 0s, fitting with checkboard pattern as 
%% indicated by phase p
%% n: length of sequences
%% p: phase of checkboard 
hidden = 0; 

%% Generate a pattern to match the side
if (mod(n,2) == 0)
   hidden = (0:2:(n-2)) + p; 
else 
   hidden  = (1:2:(n-2));
   if (p == 1)
      hidden = [hidden + 1 0];
   endif
end
hidden = 2 .^ hidden;
hidden = sum(hidden);
end
