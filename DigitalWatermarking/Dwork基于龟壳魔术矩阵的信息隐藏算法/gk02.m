turtle=zeros(256,256);
turtle(1,1)=6; turtle (2,1)=4; 
for i=3:2:255
    turtle(i,1)=mod((turtle((i-2),1)-5),8);
end
for i=4:2:256
    turtle(i,1)=mod((turtle((i-2),1)-5),8);
end
for i=1:256
    for j=2:256
        turtle(i,j)=mod(turtle(i,j-1)+1 , 8);
    end
end
        %构建龟壳矩阵

I=imread('7.bmp');
for i=1:512
    for j=1:512
        if (I(i,j)<=32)
            I(i,j)=0;
        elseif (I(i,j)<=64)
            I(i,j)=1;
        elseif (I(i,j)<=96)
            I(i,j)=2;
        elseif (I(i,j)<128)
        	I(i,j)=3;
        elseif (I(i,j)<=160)
            I(i,j)=4;
        elseif (I(i,j)<=192)
            I(i,j)=5;
        elseif (I(i,j)<=224)
            I(i,j)=6;
        elseif (I(i,j)<=256)
            I(i,j)=7;
        end
    end
end
%制作信息矩阵
stego=I(1:100,1:100);%截取100*100的矩阵作为秘密信息


co=imread('9.bmp');
cover=co;
for i=1:512
    for j=1:512
        if(cover(i,j)==0 || cover(i,j)==1)
            cover(i,j)=2;
        end
    end 
end             %导入载体图像并去除边缘数值的影响


for op=1:10000  %秘密信息一共10000个
    sr=ceil(op/100);  sl=op-(100*(sr-1));
    s=stego(sr,sl);     
    cr1=ceil(op/256);  cl1=2*(op-(256*(cr1-1)))-1;
    cr2=cr1;  cl2=cl1+1;        %建立操作数和各矩阵索引间的联系
    
    tr=cover(cr1,cl1);  tl=cover(cr2,cl2);
    if(turtle(tr,tl)~=s)
       if(turtle(tr-1,tl)==s)
           cover(cr1,cl1)=cover(cr1,cl1)-1;
           continue;
       end
       if(turtle(tr+1,tl)==s)
           cover(cr1,cl1)=cover(cr1,cl1)+1;
           continue;
       end
       if(turtle(tr,tl-1)==s)
           cover(cr2,cl2)=cover(cr2,cl2)-1;
           continue;
       end
       if(turtle(tr,tl+1)==s)
           cover(cr2,cl2)=cover(cr2,cl2)+1;
           continue;
       end
       if(turtle(tr-1,tl-1)==s)
           cover(cr1,cl1)=cover(cr1,cl1)-1;
           cover(cr2,cl2)=cover(cr2,cl2)-1;
       end
       if(turtle(tr-1,tl+1)==s)
           cover(cr1,cl1)=cover(cr1,cl1)-1;
           cover(cr2,cl2)=cover(cr2,cl2)+1;
       end
       if(turtle(tr+1,tl-1)==s)
           cover(cr1,cl1)=cover(cr1,cl1)+1;
           cover(cr2,cl2)=cover(cr2,cl2)-1;
       end
       if(turtle(tr+1,tl+1)==s)
           cover(cr1,cl1)=cover(cr1,cl1)+1;
           cover(cr2,cl2)=cover(cr2,cl2)+1;
       end
    end
end         %利用龟壳改进算法实现信息隐藏

figure;
subplot(1,2,1); imshow(co);  title('原图');
subplot(1,2,2); imshow(cover);  title('加密图像');
    %对比加密前后的图像



infor=zeros(100:100);
for op=1:10000
    ir=ceil(op/100);  il=op-(100*(ir-1));
    cr1=ceil(op/256);  cl1=2*(op-(256*(cr1-1)))-1;
    cr2=cr1;  cl2=cl1+1; 
    tr=cover(cr1,cl1);  tl=cover(cr2,cl2);
    infor(ir,il)=turtle(tr,tl);
end         %提取秘密信息

if(infor==stego)
    fprintf('提取秘密信息成功');
end 

