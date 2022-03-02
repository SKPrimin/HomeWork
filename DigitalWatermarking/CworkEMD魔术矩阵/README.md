# EMD魔术矩阵

## 实验目标

1.编程实现EMD魔术矩阵。
2.读取载体图像并设计秘密信息。
3.设计并实现EMD信息隐藏算法，将秘密信息嵌入载体图像中 。
4.提取嵌入的秘密信息。

## 实验步骤

### 01EMD魔术矩阵

```matlab
%% 实现EMD魔术矩阵
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
```

得到如下的矩阵

![image-20211019020748498](E:\cpg_file\matlab\digitalwatermarking\Cwork\EMD.assets\image-20211019020748498.png)

### 02读取载体图像并设计秘密信息

```matlab
%% 读取载体图像
cover=imread('9.bmp');
subplot(221),imshow(cover),title('载体图像');
%% 生成5进制的秘密数据
rc=100;
data=imread('7.bmp');
data=data(1:rc,1:rc);%取图片左上角rc*rc的矩阵
ori_data=data;
subplot(222),imshow(data),title('截取的图像');
data=dec2base(data,5);%像素转5进制
data=data';
data=data(:);%转置之后再转成列向量
data=str2num(data);
len=numel(data);%秘密数据长度
```

### 03将秘密信息嵌入载体图像中 

```matlab
%% 嵌入秘密数据
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
subplot(223),imshow(stegoi),title('载密图像');
```

### 04提取嵌入的秘密信息

```matlab
%% 提取秘密数据
exdata=zeros(len,1);
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
if data==exdata
    disp('提取的秘密数据与原秘密数据一致')
else
    disp('提取的秘密数据与原秘密数据不一致')
end
%% 根据提取的数据恢复出图像
exdata=reshape(exdata,4,rc*rc);
dec_data=zeros(1,rc*rc);
for i=1:rc*rc
    dec_data(i)=exdata(1,i)*5^3+exdata(2,i)*5^2+exdata(3,i)*5+exdata(4,i);
end
dec_data=uint8(reshape(dec_data,rc,rc));
subplot(224),imshow(dec_data),title('根据提取数据得到的图像');
if ori_data==dec_data
    disp('提取的图像与原图像一致')
else
    disp('提取的图像与原图像不一致')
end
```

![image-20211019020607906](E:\cpg_file\matlab\digitalwatermarking\Cwork\EMD.assets\image-20211019020607906.png)

