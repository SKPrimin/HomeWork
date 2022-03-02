
I = imread('D:\Pictures\Camera Roll\mypic.jpg'); %读入彩图
[long,width,~]=size(I); %获取图片的长度、宽度
side = 200; %想要截取的边长
i = imcrop(I,[long/2-side/2 width/2-side/2 side side]); %裁剪出一块方形区域

%将原图中的区域使用白色填充，以实现裁剪调的效果，在R、G、B范围内均填充
for k = 1:3
    I((long-side)/2:(long+side)/2,(width-side)/2:(width+side)/2,k)=255;
end

%  创建新的窗口；展示图片；保存图片
figure;imshow(I),title('彩图分割余下部分');imwrite(I,'彩图分割结果_余下部分.bmp')
figure;imshow(i),title('彩图分割裁剪部分');imwrite(i,'彩图分割结果_裁剪部分.bmp')