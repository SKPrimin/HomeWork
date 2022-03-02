I=imread('9.tiff') ;
for a=1:512
    for b=1:512
        if(I(a, b)>=0 && I(a, b)<51)
            I(a, b)=O;
        else if (I(a, b)>50 && I(a, b)<101)
            I(a, b)=1;
        else if (I(a, b)>100 && I(a, b)<151)
            I(a, b)=2;
        else if (l(a, b)>150 && I(a, b)<201)
            I(a, b)=3;
        else if(I(a,b)>200 && I(a, b)<256)
            I(a, b)=4;
            end
            end
            end
            end
        end
    end
end

%制作秘密信息.矩阵
stego=I(1:15,1:15);
%截取前225个数字作为秘密信息
