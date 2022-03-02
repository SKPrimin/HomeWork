function exdata=CbCr_de(stegoi)
[s,~]=size(stegoi);
blc=8*ones(1,s/8);
blocks=mat2cell(stegoi,blc,blc);%每块大小为8*8，一共是(s/8)*(s/8)块
getLSB=@(A)bitget(A,1);%匿名函数，取矩阵中每一个元素的最低位
stegoiLSB=cellfun(getLSB,blocks,'UniformOutput',false);%取每一块的LSB
exdata=zeros(s/8*s/8,1);
for i=1:s/8*s/8
    num1=sum(sum(stegoiLSB{i}));%1的个数
    num0=8*8-num1;%0的个数
    if num0>=num1
        exdata(i)=0;
    else
        exdata(i)=1;
    end
end