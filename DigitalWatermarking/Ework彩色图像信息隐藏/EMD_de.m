function exdata=EMD_de(stegoi,len,mag)
%% 提取秘密数据
exdata=zeros(len,1);
num=numel(stegoi);
k=1;
for i=1:2:num
    if k>=len
        break;
    end
    row=stegoi(i);
    col=stegoi(i+1);
    exdata(k)=mag(row,col);
    k=k+1;
end