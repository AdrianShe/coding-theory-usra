load test_third_moment.txt
weights = 2 .^ [-10:0.1:10]; 
raw_density = zeros(15, length(weights));
raw_variance = zeros(15, length(weights));
raw_skewness =  zeros(15, length(weights));
normalized_density = zeros(15, length(weights));
normalized_variance = zeros(15, length(weights));
%normalized_skewness = zeros(15, length(weights));
for i=2:15
  raw_density(i,:) = density(moments, weights, i);
  raw_variance(i,:) = compute_variance(moments, weights, i);
 % raw_skewness(i,:) = compute_skewness(moments, weights, i);
  normalized_density(i,:) = raw_density(i,:) / i^2;
  normalized_variance(i,:) = raw_variance(i,:) / i^2;
 % normalized_skewness(i,:) = raw_skewness(i,:) / i^2;
end

plot(-10:0.1:10, normalized_variance(6:15,:)');

%{
 for i=2:15
  h = plot(-10:0.1:10, normalized_density(i,:)) 
  axis([-10, 10, 0, 0.55]);
  title(sprintf('Normalized Density for %d by %d', i, i)); 
  ylabel('Normalized Density');
  xlabel('Log z');
  saveas(h, strcat('pngs/', sprintf('test_density_fewer%d', i), '.png'));
end

for i=2:15
  h = plot(-10:0.1:10, normalized_variance(i,:)) 
  axis([-10, 10, 0, 0.15]);
  title(sprintf('Normalized Variance for %d by %d', i, i)); 
  ylabel('Normalized Variance');
  xlabel('Log z');
  saveas(h, strcat('pngs/', sprintf('test_variance_fewer%d', i), '.png'));;
end

for i=2:15
  h = plot(-10:0.1:10, normalized_skewness(i,:)) 
  %% axis([-10, 10, 0, 0.05]);
  title(sprintf('Normalized Skewness for %d by %d', i, i)); 
  ylabel('Normalized Skewness');
  xlabel('Log z');
  saveas(h, strcat('pngs/', sprintf('test_skewness_fewer%d', i), '.png'));;
end }%


