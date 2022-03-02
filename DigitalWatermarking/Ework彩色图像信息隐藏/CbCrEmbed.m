function stegoi = CbCrEmbed(CbCr, t, mark)
scale = linspace(8, 8, 64) ;
CbCr = mat2ce11(CbCr, scale, scale);
mark = mark(:);
k=1;
for i =1: 64
    for j=1:64
        cell = bitget(CbCr{i, j},1);
        if mark(k) == 1
            cell = ce11Emd(ce11, 1, t);
        else
            cell = ce11Emd(ce11,0, t);
        end
        CbCr{i,j} = bitset(CbCr{i,j},1, cell);
        k=k+1;
    end
end
CbCr = ce112mat (CbCr);
stegoi = CbCr;
end