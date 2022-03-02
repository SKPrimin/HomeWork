%% 嵌入第一层水印
%cb嵌入信息
T=20;%阈值
watermark1_len=numel(watermark1);
newcb=CbCr_embde(cb,watermark1(1:watermark1_len/2),T);
%cr嵌入信息
newcr=CbCr_embde(cr,watermark1(watermark1_len/2+1:end),T);