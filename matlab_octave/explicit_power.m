function [eigenval, record] = explicit_power(T, tol, vec)
     %% Compute the capacity using power method
     %% of a hard square with width n.    
     %% Power Method algorithm with explicit matrix T
     record = [1];
     num_its = 1;
     while (1) 
          new_vec = T * vec;
          new_vec = new_vec / norm(new_vec);
          n = norm(vec - new_vec);
          record = horzcat(record, n);
          printf('The norm difference is %e \n', n)
          fflush(stdout);
          num_its += 1;
          if (abs(record(num_its) - record(num_its - 1)) <= tol)
              break;
          endif
          vec = new_vec;
     endwhile
    
     %% Return value of eigenvalue
     eigenval = new_vec' * (T * new_vec);
end
