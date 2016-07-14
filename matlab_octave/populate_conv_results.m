for i=1:2001
   convergence_results{i} = zeros(13, 20); 
   for j=1:13
     if (mod(j,2) == 0)
       convergence_results{i}(j,:) = checkboard_results{j,i}(19,:);
    else
       convergence_results{i}(j,:) = checkboard_results{j,i}(20,:);
    end
   end
end

final_matrix = zeros(20, 2001);

for i=1:20
   for j=1:2001
      final_matrix(i,j) = checkboard_results{13, j}(20, i);  
   end
end
