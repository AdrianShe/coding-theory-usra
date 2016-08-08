function [eigenval] = explicit_power(T, tol, vec, print_progress = false)
     %% Compute the capacity using power method
     %% of a hard square with width n.    
     %% Power Method algorithm with explicit matrix T
     old_norm = 0;
     while (1) 
          new_vec = T * vec;
          new_vec = new_vec / norm(new_vec);
          new_norm = norm(vec - new_vec);
   
          if (print_progress)
          	 printf('The norm difference is %e \n', new_norm);
         	 fflush(stdout);
          end
  
          if (abs(new_norm - old_norm) <= tol)
              break;
          endif
          vec = new_vec;
          old_norm = new_norm;
     endwhile
    
     %% Return value of eigenvalue
     eigenval = new_vec' * (T * new_vec);
end
