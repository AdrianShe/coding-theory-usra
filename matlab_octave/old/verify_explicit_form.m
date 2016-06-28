matrix = [1 1; 1 0];
fib = [1 1]; 
vec = [1; 1];

for i=3:50
  vec = matrix * vec;
  fib(i) = vec(1);
endfor 

%constant = [((1 + sqrt(2)) / 2) ((2 + sqrt(2)) / 4) ((2 + sqrt(2)) / 4)];

results = zeros(40, 1);
eig = 1 + sqrt(2);
for b=1:40
  top = (4 + 3 * sqrt(2)) * fib(b+2) + (2 + sqrt(2)) * fib(b+1);
  bottom = (4 + 3 * sqrt(2)) * fib(b+3) + (2 + sqrt(2)) * fib(b+2);
  results(b) = (top / bottom) * (1 + sqrt(2));
endfor
