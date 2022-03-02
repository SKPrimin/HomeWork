close all;
clear;
clc;
%% 读取原始图像，分成8×8的块
img_original = imread("7.bmp");
subplot(121),imshow(img_original),title('原始图像');
[rc,~] = size(img_original);
bottom_plate = 8*ones(1,rc/8);
blocks = mat2cell(img_original,bottom_plate,bottom_plate);%分成8×8的块
%% 8×8的块进行JPEG数据压缩
Q = [16,11,10,16,24,40,51,61;
    12,12,14,19,26,58,60,55;
    14,13,16,24,40,57,69,56;
    14,17,22,29,51,87,80,62;
    18,22,37,56,68,109,103,77;
    24,35,55,64,81,104,113,92;
    49,64,78,87,103,121,120,101;
    72,92,95,98,112,100,103,99
    ];%标准量化矩阵
%匿名函数，对每一块进行DCT变换后量化，并取整
quantify = @(A)round(matrixChanges(dct2(double(A)),2)./Q);
qt_fmsg = cellfun(quantify,blocks,'UniformOutput',false);
quant_stegoi = int8(cell2mat(qt_fmsg));%取整
%% 设计水印信息
watermark_information = 'SKPrimin';
data = abs(watermark_information);
data = dec2bin(data);
data = data';
data = str2num(data(:));
data_length = numel(data);
%% LSB算法嵌入水印信息，得到嵌入水印的JPEG压缩数据。
k = 1;
qtstg_length = numel(quant_stegoi);
for i = 1:qtstg_length
    if k>data_length
        break;
    end
    if abs(quant_stegoi(i))>1 && quant_stegoi(i)~= -2
        quant_stegoi(i) = bitset(quant_stegoi(i),1,data(k));
        k = k+1;
    end
end
%% 嵌入水印的JPEG压缩数据解压缩后显示
stegoi_blocks = mat2cell(quant_stegoi,bottom_plate,bottom_plate);%分成8×8的块

%匿名函数，对每一块进行逆量化、逆DCT变换
inversequantify = @(A)idct2(matrixChanges((double(A).*Q),1));
qt_inversemsg = cellfun(inversequantify,stegoi_blocks,'UniformOutput',false);
inverseqt_stegoi = uint8(cell2mat(qt_inversemsg));
subplot(122),imshow(inverseqt_stegoi),title('载密图像');
%% 提取秘密信息
inverseqt_stegoi = double(inverseqt_stegoi);
newblocks = mat2cell(inverseqt_stegoi,bottom_plate,bottom_plate);%分成8×8的块
qt_lmsg = cellfun(quantify,newblocks,'UniformOutput',false);
qt_mat = int8(cell2mat(qt_lmsg));%量化后的矩阵
extdata = zeros(data_length,1);
qtmat_length = numel(qt_mat);
k = 1;
for i = 1:qtmat_length
    if k>data_length
        break;
    end
    if abs(qt_mat(i))>1 && qt_mat(i)~= -2
        extdata(k) = bitget(qt_mat(i),1);
        k = k+1;
    end
end
if data == extdata
    disp('秘密信息提取成功');
    datafirst = num2str(extdata);
    datasecond = reshape(datafirst,7,data_length/7);
    tempthird = datasecond';
    tempfourth = zeros(1,data_length/7);
    for i = 1:data_length/7
        tempfourth(i) = bin2dec(tempthird(i,:));
    end
    demsg = char(tempfourth);
    fprintf('提取到的水印信息为：%s\n',demsg)
else
    disp('秘密信息提取不成功');
end