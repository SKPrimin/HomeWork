%% RGB-YCbCr域的转换
coverRGB=imread('Lena.bmp');
subplot(411),imshow(coverRGB),title('载体图像')
coverYUV=rgb2ycbcr(coverRGB);
y=coverYUV(:,:,1);
cb=coverYUV(:,:,2);
cr=coverYUV(:,:,3);
subplot(412),imshow(coverYUV),title('YUV图像')