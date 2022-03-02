function stegoi = cellEmd(ce11,n, t)
zero = double(sum(ce11(:) == 0));
one = double(sum(ce11(:) == 1));
    if n ==1
        for i=1:64
            if one-zero>=t
                break;
            end
            if ce11(i) = 1
                ce11(i) = 1;
                one=one+1;
                zero = zero- 1;
            end
        end
    end
    
    if n==0
        for i =1: 64
            if zero-one >= t
                break;
            end
            if ce11(i)~= 0
                ce11(i) = 0;
                one = one - 1;
                zero = zero + 1;
            end
        end
    end
    stegoi = ce11;
end