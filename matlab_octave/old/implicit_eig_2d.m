function [eigenval, record] = implicit_eig_2d(L, tol)
     %% Compute the capacity using power method
     %% of a hard square with width n.    
     %% Power Method algorithm
     D = unique(L)';
     vec = ones(length(D), 1);
     dict = create_dict(D); %% Create dictionary
      
     record = [1];
     num_its = 1;
     while (1) 
          new_vec = implicit_2d_multiply(L, dict, vec);
          new_vec = new_vec / norm(new_vec);
          record = [record norm(vec-new_vec)];
          printf('The norm difference is %e \n', norm(vec-new_vec))
          fflush(stdout);
          num_its = num_its + 1;
          if (abs(record(num_its) - record(num_its - 1)) <= tol)
              break;
          endif
          vec = new_vec;
     endwhile
    
     %% Return value of eigenvalue
     eigenval = new_vec' * implicit_2d_multiply(L, dict, new_vec);
end
