%% 第一张 风车
imgW = imread('C:\Users\SKPrimin\Desktop\ctf\211119619784cbdb9fbr.png');
imgW=imresize(imgW,0.5);
imgWsize=size(imgW);
%提取bitplane
bitPlaneW=zeros(imgWsize(1),imgWsize(2),8);
for i =1:8
    for ro=1:imgWsize(1)
        for co=1:imgWsize(2)
        bitPlaneW(ro,co,i)=bitget(imgW(ro,co), i);
        end        
    end    
end
% 绘制bitplane
figure;
for i =1:8
    subplot(2,4,i)
    imshow(uint8(255*bitPlaneW(:,:,i)))
    title(['Bitplane' num2str(i)])
end
