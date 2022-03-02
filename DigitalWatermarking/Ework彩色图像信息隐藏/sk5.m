%% EMD算法在RGB域嵌入第二层水印
B=stegoi1(:,:,3);
n=256;
m5=zeros(5,5);
for i=1:5
	m5(1,i)=i-1;
	m5(2,i)=mod(i+2,5);
	m5(3,i)=mod(i+5,5);
	m5(4,i)=mod(i+3,5);
	m5(5,i)=mod(i+1,5);
end
r=ceil(n/5);
c=ceil(n/5);
mag=repmat(m5,r,c);
mag=mag(1:n,1:n);
stegoi2(:,:,1)=stegoi1(:,:,1);
stegoi2(:,:,2)=stegoi1(:,:,2);
stegoi2(:,:,3)=EMD_em(B,fivewatermark,mag);
subplot(426),imshow(stegoi2),title('嵌入第二层水印后的图像');