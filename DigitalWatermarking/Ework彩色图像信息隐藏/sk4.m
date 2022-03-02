%% YCbCr-RGB域的转换
stegoi1(:,:,1)=y;
stegoi1(:,:,2)=newcb;
stegoi1(:,:,3)=newcr;
stegoi1=ycbcr2rgb(stegoi1);
subplot(425),imshow(stegoi1),title('嵌入第一层水印后的载密图像')
p1=psnr(stegoi1,coverRGB);