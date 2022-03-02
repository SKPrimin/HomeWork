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