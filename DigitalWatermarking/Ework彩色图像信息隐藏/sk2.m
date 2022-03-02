%% 设计水印信息
%第一层水印
watermark1=imread('52.bmp');
%截取左上角40*40的图片作为水印
watermark1=watermark1(1:40,1:40);
origin_watermark1=watermark1;
subplot(413),imshow(watermark1),title('第一层水印图像');
watermark1=dec2bin(watermark1);
watermark1=watermark1';
watermark1=str2num(watermark1(:));%一层信息转为二进制保存
watermark2=coverRGB(:,:,3);%将B通道的最高位作为第二层水印
watermark2=bitget(watermark2,8);
subplot(414),imshow(bitshift(watermark2,7)),title('第二层水印图像');
origin_watermark2=watermark2;
watermark2=num2str(watermark2(:));%二进制的秘密信息
watermark2=reshape(watermark2,512*512/8,8);
tenwatermark=zeros(512*512/8,1);%十进制的秘密信息
for i=1:512*512/8
    tenwatermark(i)=bin2dec(watermark2(i,:));
end
fivewatermark=dec2base(tenwatermark,5);
fivewatermark=fivewatermark';
fivewatermark=str2num(fivewatermark(:));%二层信息转成五进制保存