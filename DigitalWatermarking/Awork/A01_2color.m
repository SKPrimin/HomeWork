I = imread('D:\Python_FILE\Spyder\PJaRm\dataset\lena.png');

IR=I(:,:,1);
IG=I(:,:,2);
IB=I(:,:,3);
imshow(I),title('彩图打开显示')