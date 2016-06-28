function [compat] = generate_checkboard_compat(S, n, p) 
%% S: list of sequences
%% n: size of sequences
%% p: phase of checkboard
%% return boolean vector of comptabilities

%% odd n means same phase
compat = ones(length(S), 1);
if (mod(n, 2) == 1 && p == 0) %% everything is compitable in this case
   return;
end

if ((mod(n, 2) == 0 && p == 0) || (mod(n,2) == 1 && p == 1))
     %% sequences cannot be odd in this case
     for i=1:length(S)
        if (mod(S(i), 2) == 1)
           compat(i) = 0;
        end
     end
end

if ((mod(n, 2) == 0 && p == 1) || (mod(n,2) == 1 && p == 1))
     %% sequences cannot be >= 2^n-1 in this case
     for i=1:length(S)
        if (S(i) >= 2^(n-1)) 
           compat(i) = 0;
        end
      end
end
end
