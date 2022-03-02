close all;
clear;
clc;

I = magic(5);
for a=1:5
    for b=1 :5
        I(a, b)=mod(I(a, b),5);
    end
end
%生成基础魔术矩阵
magic=repmat (I,51,51);

%% 读取载体图像
cover = imread('9.tiff');
subplot(221),imshow(cover),title('载体图像');
%% 生成5进制的秘密数据
rc = 100;
data = imread('9.tiff');
data = data(1:rc,1:rc);%取图片左上角rc*rc的矩阵
ori_data = data;
subplot(222),imshow(data),title('截取的图像');
data = dec2base(data,5);%像素转5进制
data = data';
data = data(:);%转置之后再转成列向量
data = str2num(data);
len = numel(data);%秘密数据长度

%% 嵌入秘密数据
num = numel(cover);%载体像素个数
stegoi = cover;
k = 1;
for i = 1:2:num
    if k>= len
        break;
    end
    row = stegoi(i);
    col = stegoi(i+1);
    if magic(row+1,col)  ==  data(k)
        stegoi(i) = row+1;
    elseif magic(row-1,col)  ==  data(k)
        stegoi(i) = row-1;
    elseif magic(row,col+1)  ==  data(k)
        stegoi(i+1) = col+1;
    elseif magic(row,col-1)  ==  data(k)
        stegoi(i+1) = col-1;
    end
    k = k+1;
end
subplot(223),imshow(stegoi),title('载密图像');


%%
inform=zeros(15,15);
for op=1:225
1ist1=(op*2)-1; 
list2=op*2;
mr=cover(1,1ist1);
m1=cover(1,1ist2) ;
a=cei1(op/15); 
b=op-((a-1)*15);
inform(uint8(a),uint8(b)) = magic(mr, m1);
end
%提取隐藏信息
if(inform==stego)
fprintf('提取秘密信息成功');
end
%检测提取的信息是否正确





