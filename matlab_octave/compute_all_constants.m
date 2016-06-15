function [vals] = compute_all_constants(T1, T2, E, a, b, c)
   %% b: the maximum value of b
   %% c: the maximum value of c
  
   T1_cell = cell(b+1, 1);
   T2_cell = cell(c+1, 1);

   %% initialize T1
   T1_cell{1} = eye(rows(T1));
   T1_cell{2} = T1; 
   
   %% initalize T2
   T2_cell{1} = eye(rows(T2));
   T2_cell{2} = T2;
 
   printf('Computing T1 powers \n');
   for i=3:(b+1)
     T1_cell{i} = T1_cell{i-1} * T1;
   endfor
   printf('Finished computing T1 powers \n');

   printf('Computing T2 powers \n');
   for j=3:(c+1)
     T2_cell{j} = T2_cell{j-1} * T2;
   endfor
   printf('Finished computing T2 powers \n');
 
   ones_vector = ones(rows(T1), 1);
   for i=1:b
    for j=2:c
     number_top = T2_cell{j-1} * E * T1_cell{i+1} * ones_vector;
     number_bottom = T2_cell{j} * E * T1_cell{i} * ones_vector;
     vals(i,j-1) = sum(number_bottom) / sum(number_top);
     fprintf('%d %d %d \n', a, i, j); 
     fflush(stdout);
     endfor
   endfor
end
