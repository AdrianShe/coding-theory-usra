z = 2 .^ [-1:0.01:10];
a = 2:12;
res = cell(length(a), 1); 
b= 1:20;
c= 1:20;
for i=1:length(a)
  res{i} = compute_checkboard_main(a(i), b, c, z, 0); 
end
