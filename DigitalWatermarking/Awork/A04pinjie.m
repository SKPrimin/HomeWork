%读入图片
B = imread('黑白分割结果_余下部分.bmp');
C = imread('彩图分割结果_余下部分.bmp');
I = imread('D:\Pictures\misc标准库\50.bmp');
% 获取图片的长与宽
[long1, width1] = size(B);
[long2, width2,~] = size(C);
[long3, width3] = size(I);

limit = 200;%希望截取的长度
i = I((long3-limit)/2:(long3+limit)/2,(width3-limit)/2:(width3+limit)/2);
%填充黑白图B
B((long1-limit)/2:(long1+limit)/2,(width1-limit)/2:(width1+limit)/2) = i;
%填充彩图C
for k = 1:3
    C((long2-limit)/2:(long2+limit)/2,(width2-limit)/2:(width2+limit)/2,k) = i;
end

figure;imshow(B);imwrite(B,'黑白拼接结果.bmp');
figure;imshow(C);imwrite(C,'彩图拼接结果.bmp');
