function [S] = generate_ring_sequences(n)
   %% Generates the list of binary strings
   %% of length n with no adjacent 1s 
   %% n: length of string
   %% and head and tail cannot by simultaneously 1
   
   if (n == 0)
       S = zeros(1,0);
   endif
   if (n==1)
       S = [0];
   endif
   if (n==2)
       S = [ 0 0 ; 0 1 ; 1 0];
   endif
   if (n>=3)
       end_in_zero = generate_sequences(n-1);
       rows_end_in_zero = rows(end_in_zero);
       end_in_zero = [end_in_zero zeros(rows_end_in_zero,1) ]; 
       
       end_in_one = generate_sequences(n-3);
       rows_end_in_one = rows(end_in_one);
       end_in_one = [zeros(rows_end_in_one,1) end_in_one zeros(rows_end_in_one,1) ones(rows_end_in_one,1)]; 

       S = [ end_in_zero ; end_in_one ];
    endif
    %%   printf('Rows');
    %%   rows(S)
end 
