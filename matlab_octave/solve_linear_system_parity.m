%% Produce local approximation of sufrace press and energy energy
%% from finite dimensional system.

load 2_16_-10_10_hundredth_moments.txt
approx_a = zeros(11, 2001);
approx_kappa = zeros(11, 2001);
approx_rho = zeros(11, 2001);

for n=6:16
	matrix = [1 n^2 n; 1 (n-2)^2 n-2; 1 (n-4)^2 n-4]
        fflush(stdout)
	approx = zeros(3, 2001);
	for i=1:2001
		vec = log([moments{n-1}(1,i); moments{n-3}(1,i); moments{n-5}(1,i)]);
		approx(:,i) = matrix \ vec;
	end
        approx_a(n-5,:) = approx(1,:);
        approx_kappa(n-5,:) = approx(2,:);
        approx_rho(n-5,:) = approx(3,:);
end
