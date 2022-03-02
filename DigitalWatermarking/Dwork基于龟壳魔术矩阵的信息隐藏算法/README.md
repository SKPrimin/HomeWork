# 基于龟壳魔术矩阵的信息隐藏算法

## 实验内容

1. 编程实现龟壳魔术矩阵
2. 读取载体图像并设计秘密信息
3. 设计并实现龟壳信息隐藏算法，将秘密信息嵌入载体图像中 
4. 提取嵌入的秘密信息。

## 实验步骤

#### 编程实现龟壳魔术矩阵

```matlab
%% 生成龟壳矩阵
turtmat=zeros(256);
turtmat(1,1)=6;
%第一行
for j=2:256
    turtmat(1,j)=mod(turtmat(1,j-1)+1,8);
end
%第2-256行
for i=2:256
    if mod(i,2)==0
        turtmat(i,:)=mod(turtmat(i-1,:)-2,8);
    else
        turtmat(i,:)=mod(turtmat(i-1,:)-3,8);
    end
end
```

![image-20211019015234450](龟壳.assets\image-20211019015234450.png)

#### 读取载体图像并设计秘密信息

```matlab
%% 读取载体图像并设计秘密信息
cover=imread('9.bmp');
subplot(221),imshow(cover),title('载体图像');
%% 生成8进制的秘密数据
rc=200;
data=imread('76.bmp');
data=data(1:rc,1:rc);%取图片左上角rc*rc的矩阵
ori_data=data;
subplot(222),imshow(data),title('截取的图像');
data=dec2base(data,8);%像素转8进制
data=data';
data=data(:);%转置之后再转成列向量
data=str2num(data);
len=numel(data);%秘密数据长度
```

#### 将秘密信息嵌入载体图像中

```matlab
%% 嵌入秘密数据
num=numel(cover);%载体像素个数
stegoi=cover;
k=1;
for i=1:2:num
    if k>len
        break;
    end
    row=stegoi(i);
    col=stegoi(i+1);
    if turtmat(row+1,col)==data(k)
        stegoi(i)=row+1;
        flag=1;%在上下左右找到了
    elseif turtmat(row-1,col)==data(k)
        stegoi(i)=row-1;
        flag=1;
    elseif turtmat(row,col+1)==data(k)
        stegoi(i+1)=col+1;
        flag=1;
    elseif turtmat(row,col-1)==data(k)
        stegoi(i+1)=col-1;
        flag=1;
    else
        flag=0;%在上下左右没找到
    end
    if flag==0 %在四个角上找
        if turtmat(row+1,col+1)==data(k)
            stegoi(i)=row+1;
            stegoi(i+1)=col+1;
        elseif turtmat(row+1,col-1)==data(k)
            stegoi(i)=row+1;
            stegoi(i+1)=col-1;
        elseif turtmat(row-1,col+1)==data(k)
            stegoi(i)=row-1;
            stegoi(i+1)=col+1;
        elseif turtmat(row-1,col-1)==data(k)
            stegoi(i)=row-1;
            stegoi(i+1)=col-1;
        end
    end
    k=k+1;
end
subplot(223),imshow(stegoi),title('载密图像');
```

#### 提取嵌入的秘密信息

```matlab
%% 提取秘密数据
exdata=zeros(len,1);
k=1;
for i=1:2:num
    if k>len
        break;
    end
    row=stegoi(i);
    col=stegoi(i+1);
    exdata(k)=turtmat(row,col);
    k=k+1;
end
if data==exdata
    disp('提取的秘密数据与原秘密数据一致')
else
    disp('提取的秘密数据与原秘密数据不一致')
end
%% 根据提取的数据恢复出图像
exdata=reshape(exdata,3,rc*rc);
dec_data=zeros(1,rc*rc);
for i=1:rc*rc
    dec_data(i)=exdata(1,i)*8^2+exdata(2,i)*8+exdata(3,i);
end
dec_data=uint8(reshape(dec_data,rc,rc));
subplot(224),imshow(dec_data),title('提取到的图像');
if ori_data==dec_data
    disp('提取的图像与原图像一致')
else
    disp('提取的图像与原图像不一致')
end
```

![image-20211019015519285](龟壳.assets\image-20211019015519285.png)

