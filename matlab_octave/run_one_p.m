origin = zeros(200, 1);
for i=1:200
   fprintf('%d boxes', i)
   origin(i) = compute_one_param_box(i, 'n');
   fflush(stdout)
end