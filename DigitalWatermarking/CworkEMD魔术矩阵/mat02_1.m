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



