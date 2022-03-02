function stegoi=EMD_em(cover,data,mag)
%% 嵌入秘密数据
len=numel(data);%秘密信息长度
num=numel(cover);%载体像素个数
stegoi=cover;
k=1;
for i=1:2:num
    if k>=len
        break;
    end
    row=stegoi(i);
    col=stegoi(i+1);
    if mag(row+1,col)==data(k)
        stegoi(i)=row+1;
    elseif mag(row-1,col)==data(k)
        stegoi(i)=row-1;
    elseif mag(row,col+1)==data(k)
        stegoi(i+1)=col+1;
    elseif mag(row,col-1)==data(k)
        stegoi(i+1)=col-1;
    end
    k=k+1;
end