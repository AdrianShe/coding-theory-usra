%% Produce local approximation of surface pressure and energy 
%% from finite dimensional system.

%load 2_16_-10_10_hundredth_moments.txt
height = 11;
width = 401;
%load checkboard_moments.txt
approx_a_0 = zeros(height, width);
approx_kappa_0 = zeros(height, width);
approx_rho_0 = zeros(height, width);
approx_a_1 = zeros(height, width);
approx_kappa_1 = zeros(height, width);
approx_rho_1 = zeros(height, width);


%moment = checkboard_1

for n=6:16
	matrix = [1 n^2 n; 1 (n-2)^2 n-1; 1 (n-4)^2 n-2]
        fflush(stdout)
	approx = zeros(3, width);
	for i=1:width
		vec_0 = log([checkboard_0{n-1}(1,i); checkboard_0{n-3}(1,i); checkboard_0{n-5}(1,i)]);
 		vec_1 = log([checkboard_1{n-1}(1,i); checkboard_1{n-3}(1,i); checkboard_1{n-5}(1,i)]);
		approx_0(:,i) = matrix \ vec_0;
                approx_1(:,i) = matrix \ vec_1;
	end
        approx_a_0(n-5,:) = approx_0(1,:);
        approx_kappa_0(n-5,:) = approx_0(2,:);
        approx_rho_0(n-5,:) = approx_0(3,:);
        approx_a_1(n-5,:) = approx_1(1,:);
        approx_kappa_1(n-5,:) = approx_1(2,:);
        approx_rho_1(n-5,:) = approx_1(3,:);
end

%approx_a_free = approx_a_free(:,1:5:2001);
%approx_kappa_free = approx_kappa_free(:,1:5:2001);
%approx_rho_free = approx_rho_free(:,1:5:2001);
