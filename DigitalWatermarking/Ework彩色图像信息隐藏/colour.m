close all;
clear;
clc;
%% RGB-YCbCr域的转换
coverRGB=imread('Lena.bmp');
subplot(411),imshow(coverRGB),title('载体图像')
coverYUV=rgb2ycbcr(coverRGB);
y=coverYUV(:,:,1);
cb=coverYUV(:,:,2);
cr=coverYUV(:,:,3);
subplot(412),imshow(coverYUV),title('YUV图像')
%% 设计水印信息
%第一层水印
water1=imread('52.bmp');
%截取左上角32*32的图片作为水印
water1=water1(1:32,1:32);
ori_water1=water1;
subplot(423),imshow(water1),title('第一层水印图像');
water1=dec2bin(water1);
water1=water1';
water1=str2num(water1(:));%最终变成二进制的秘密信息
%第二层水印是B通道的最高位
water2=coverRGB(:,:,3);
water2=bitget(water2,8);
subplot(424),imshow(bitshift(water2,7)),title('第二层水印图像');
ori_water2=water2;
water2=num2str(water2(:));%二进制的秘密信息
lon=8;%8位二进制，表示一个十进制
water2=reshape(water2,512*512/lon,lon);
dec_water2=zeros(512*512/lon,1);%十进制的秘密信息
for i=1:512*512/lon
    dec_water2(i)=bin2dec(water2(i,:));
end
base5_water2=dec2base(dec_water2,5);
base5_water2=base5_water2';
base5_water2=str2num(base5_water2(:));%最终变成五进制的秘密信息
%% 嵌入第一层水印
%cb嵌入信息
p1=zeros(1,31);
p2=p1;
p3=p1;
p4=p1;
T=10;%阈值
water1_len=numel(water1);
newcb=CbCr_em(cb,water1(1:water1_len/2),T);
%cr嵌入信息
newcr=CbCr_em(cr,water1(water1_len/2+1:end),T);
%% YCbCr-RGB域的转换
stegoi1(:,:,1)=y;
stegoi1(:,:,2)=newcb;
stegoi1(:,:,3)=newcr;
stegoi1=ycbcr2rgb(stegoi1);
subplot(425),imshow(stegoi1),title('嵌入第一层水印后的载密图像')

%% EMD算法在RGB域嵌入第二层水印
B=stegoi1(:,:,3);%在B通道嵌入信息
%实现EMD魔术矩阵
n=256;
m5=zeros(5,5);%先生成5*5的
for i=1:5
    m5(1,i)=i-1;
    m5(2,i)=mod(i+2,5);
    m5(3,i)=mod(i+5,5);
    m5(4,i)=mod(i+3,5);
    m5(5,i)=mod(i+1,5);
end
r=ceil(n/5);
c=ceil(n/5);
mag=repmat(m5,r,c);%平铺
mag=mag(1:n,1:n);%只需要256*256的矩阵
stegoi2(:,:,1)=stegoi1(:,:,1);
stegoi2(:,:,2)=stegoi1(:,:,2);
stegoi2(:,:,3)=EMD_em(B,base5_water2,mag);
subplot(426),imshow(stegoi2),title('嵌入第二层水印后的图像');

%% 提取第二层水印
len2=numel(base5_water2);
exdata2=EMD_de(stegoi2(:,:,3),len2,mag);%提取到的是五进制数
exdata2=reshape(exdata2,4,512*512/lon);
dec_exdata2=zeros(1,512*512/lon);
%将五进制的秘密信息转成十进制
for i=1:512*512/lon
    dec_exdata2(i)=exdata2(1,i)*5^3+exdata2(2,i)*5^2+exdata2(3,i)*5+exdata2(4,i);
end
%将十进制的秘密信息转成二进制
bin_exdata2=dec2bin(dec_exdata2,lon);
bin_exdata2=str2num(bin_exdata2(:));
bin_exdata2=uint8(reshape(bin_exdata2',512,512));
subplot(428),imshow(bitshift(bin_exdata2,7));
title('提取到的第二层水印图像');

%% 提取第一层水印
stegoYUV=rgb2ycbcr(stegoi2);
stegoCb=stegoYUV(:,:,2);
stegoCr=stegoYUV(:,:,3);
exdata1_1=CbCr_de(stegoCb);%从Cb提取到的秘密信息
exdata1_2=CbCr_de(stegoCr);%从Cr提取到的秘密信息
exdata1=[exdata1_1;exdata1_2];%两者组合在一起
exdata1=num2str(exdata1);
exdata1=reshape(exdata1,lon,water1_len/lon);
exdata1=exdata1';
dec_exdata1=zeros(1,water1_len/lon);
%将二进制的秘密信息转成十进制
for i=1:water1_len/lon
    dec_exdata1(i)=bin2dec(exdata1(i,:));
end
dec_exdata1=reshape(dec_exdata1,32,32);
subplot(427),imshow(uint8(dec_exdata1));
title('提取到的第一层水印图像');