origin_zero = zeros(200, 1);
new_zero = zeros(200, 1);
for i=1:200
    fprintf('%d boxes \n', i)
    origin_zero(i) = compute_one_param_box(i, 'o');
    new_zero(i) = compute_one_param_box(i, 'n');
    fflush(stdout)
end

