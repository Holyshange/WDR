close all;
clear
clc

% pic1 = 'fattal3';
% pic2 = 'fattal4';

pic1 = 'house1';
pic2 = 'house2';

A = imread( strcat('.\', pic1, '.jpg'));
B = imread( strcat('.\', pic2, '.jpg'));
[M, N, K] = size(A);

Ag = rgb2gray(A);
Bg = rgb2gray(B);

A = double(A) / 255;
B = double(B) / 255;

stride = 3;
edge = (stride - 1) / 2;
stride_2 = ((stride - edge) ^ 2) + (edge ^ 2);

Ag_pad = zeros(M + stride - 1, N + stride - 1);
Bg_pad = zeros(M + stride - 1, N + stride - 1);

Ag_pad(1 + edge : M + edge, 1 + edge : N + edge) = Ag;
Bg_pad(1 + edge : M + edge, 1 + edge : N + edge) = Bg;

Ag_conv = zeros(M, N);
Bg_conv = zeros(M, N);

t = 0;
for i = 1 + edge : M + edge
	for j = 1 + edge : N + edge
		sum1 = 0;
		sum2 = 0;
		for k = i - edge : 2 : i + edge
			for l = j - edge : 2 : j + edge
				sum1 = sum1 + Ag_pad(k, l);
				sum2 = sum2 + Bg_pad(k, l);
			end
		end
		sum1 = sum1 + t * Ag_pad(i, j);
		sum2 = sum2 + t * Bg_pad(i, j);
		for k = i - edge + 1 : 2 : i + edge - 1
			for l = j - edge + 1 : 2 : j + edge - 1
				sum1 = sum1 + Ag_pad(k, l);
				sum2 = sum2 + Bg_pad(k, l);
			end
		end
		Ag_conv(i - edge, j - edge) = sum1;
		Bg_conv(i - edge, j - edge) = sum2;
	end
end

Ag_conv = uint8(Ag_conv / (stride_2 + t));
Bg_conv = uint8(Bg_conv / (stride_2 + t));

Ag_conv = double(Ag_conv) / 255;
Bg_conv = double(Bg_conv) / 255;

C = zeros(M, N, K);
D = zeros(M, N);

e = 0.5;
f = 0.5;

for i = 1 : M
	for j = 1 : N
		a = Ag_conv(i, j);
		b = Bg_conv(i, j);

		wa = (1 / (1 + power(2, 19 * (0.69 - b))));
		wb11 = (1 - 1 / (1 + power(2, 6 * (0.4 - a)))) ^ 2;
		wb12 = (1 - a) ^ 3;
		wb1 = e * wb11 + (1 - e) * wb12;
		wb2 = (1 - 1 / (1 + power(2, 15 * (0.8 - b)))) ^ 0.6;
		wb = f * wb1 + (1 - f) * wb2;
		C(i, j, :) = (wa * A(i, j, :) + wb * B(i, j, :)) / (wa + wb);
%		D(i, j) = b;
	end
end

% D = uint8(255 * D);
% imwrite(D, stract('.\', pic1, '_', pic2, '_weight.jpg'));

C = uint8(255 * C);
imwrite(C, strcat('.\', pic1, '_', pic2, '_fusion.jpg'));