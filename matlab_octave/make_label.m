label = cell(1, 20);
x_axis = -10:0.5:10;
for i=1:length(x_axis)
	if (mod(x_axis(i),5) == 0)
		label{i} = sprintf("%d", x_axis(i));
	end
end

