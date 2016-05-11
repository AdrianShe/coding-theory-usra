function [res] = implicit_1d_multiply(S, vec)
    %% Given a list of allowed sequences S
    %% and a vector indexed by S, compute
    %% the next-allowed vector S, given that
    %% the first entry of S is zero.
    res = zeros(length(vec), 1);
    res(1) = sum(vec); %% Multiply first row of vector given it is zero
    res(2:length(vec)) += vec(1); 
    for i=2:length(vec)
       for j=i:length(vec)
           if (bitand(S(i), S(j)) == 0) %% Check if sequences are compitable
              res(i) += vec(j); %% Perform "implicit" matrix multiplication
              res(j) += vec(i); %% Matrix S is symmetric
            endif
       endfor
    endfor
end
