function [res] = implicit_1d_multiply(S, vec)
    %% Given a list of allowed sequences S
    %% and a vector indexed by S, compute
    %% the next-allowed vector S
    res = zeros(length(vec), 1);
    for i=1:length(vec)
       for j=i:length(vec)
           if (bitand(S(i), S(j)) == 0) %% Check if sequences are compitable
              res(i) = res(i) + vec(j); %% Perform "implicit" matrix multiplication
              if (i != j)
                  res(j) = res(j) + vec(i); %% Multiplication performed twice if i neq j
              endif
           endif
       endfor
    endfor
end
