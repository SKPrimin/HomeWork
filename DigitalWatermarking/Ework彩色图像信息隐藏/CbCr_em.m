function stegoi=CbCr_em(cover,data,T)
[s,~]=size(cover);
blc=8*ones(1,s/8);
blocks=mat2cell(cover,blc,blc);%每块大小为8*8，一共是(s/8)*(s/8)块
getLSB=@(A)bitget(A,1);%匿名函数，取矩阵中每一个元素的最低位
coverLSB=cellfun(getLSB,blocks,'UniformOutput',false);%取每一块的LSB
k=1;
for i=1:s/8*s/8
    if data(k)==0
        num1=sum(sum(coverLSB{i}));%1的个数
        num0=8*8-num1;%0的个数
        j=1;
        while num0-num1<T
            if coverLSB{i}(j)~=0
                coverLSB{i}(j)=0;
                %将载体的每一块对应的像素的最低位做修改，下同
                blocks{i}(j)=bitset(blocks{i}(j),1,0);
            end
            j=j+1;
            num1=sum(sum(coverLSB{i}));%1的个数
            num0=8*8-num1;%0的个数
        end
    else
        num1=sum(sum(coverLSB{i}));%1的个数
        num0=8*8-num1;%0的个数
        j=1;
        while num1-num0<T
            if coverLSB{i}(j)~=1
                coverLSB{i}(j)=1;
                blocks{i}(j)=bitset(blocks{i}(j),1,1);
            end
            j=j+1;
            num1=sum(sum(coverLSB{i}));%1的个数
            num0=8*8-num1;%0的个数
        end
    end
    k=k+1;
end
stegoi=cell2mat(blocks);