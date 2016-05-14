function [S] = generate_ring_sequences_numrep(n)
   %% Generates the list of binary strings
   %% of length n with no adjacent 1s 
   %% n: length of string
   %% and head and tail cannot by simultaneously 1
   
   if (n == 0)
       S = 0;
   endif
   if (n==1)
       S = [0];
   endif
   if (n==2)
       S = [0 2 1];
   endif
   if (n>=3)
       end_in_zero = bitshift(generate_sequences_numrep(n-1), 1);
       end_in_one = bitshift(generate_sequences_numrep(n-3), 2) + 1;
       S = [ end_in_zero end_in_one ];
    endif
    %%   printf('Rows');
    %%   rows(S)
end 
