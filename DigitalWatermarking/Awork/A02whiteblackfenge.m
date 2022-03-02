
I=imread('D:\Pictures\Camera Roll\7.bmp'); %读入黑白图
[long,width]=size(I); %获取图片的长度、宽度

%希望截取的边长，截取部分为图像正中心的以limit为边长的区域
limit=200;
%裁剪出一块方形区域
i=I((long-limit)/2:(long+limit)/2,(width-limit)/2:(width+limit)/2);
%将原图中的区域使用白色填充
I((long-limit)/2:(long+limit)/2,(width-limit)/2:(width+limit)/2)=255;

%绘图并保存为新图片
figure;imshow(I),title('黑白分割余下部分');imwrite(I,'黑白分割结果_余下部分.bmp')
figure;imshow(i),title('黑白分割裁剪部分');imwrite(i,'黑白分割结果_裁剪部分.bmp')
