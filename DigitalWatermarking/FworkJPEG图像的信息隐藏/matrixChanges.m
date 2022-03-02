function matrixChangesdone = matrixChanges(mat,select)
if select == 1 %反变换
    row = [1 1 2 3 2 1 1 2
           3 4 5 4 3 2 1 1
           2 3 4 5 6 7 6 5
           4 3 2 1 1 2 3 4
           5 6 7 8 8 7 6 5
           4 3 2 3 4 5 6 7
           8 8 7 6 5 4 5 6
           7 8 8 7 6 7 8 8];
    col = [1 2 1 1 2 3 4 3
           2 1 1 2 3 4 5 6
           5 4 3 2 1 1 2 3
           4 5 6 7 8 7 6 5
           4 3 2 1 2 3 4 5
           6 7 8 8 7 6 5 4
           3 4 5 6 7 8 8 7
           6 5 6 7 8 8 7 8];
end
if select == 2 %正变换
    row = [1 1 1 1 2 2 4 4
           1 1 1 2 3 4 4 6
           1 2 2 3 4 4 6 6 
           2 2 3 4 4 6 6 7
           2 3 3 5 5 6 7 7
           3 3 5 5 6 7 7 8
           3 5 5 6 7 8 8 8 
           5 5 7 7 8 8 8 8];
    col = [1 2 6 7 7 8 4 5
           3 5 8 6 1 3 6 3
           4 1 5 2 2 7 2 4
           2 4 3 1 8 1 5 6
           3 4 8 1 8 6 5 7
           5 7 2 7 7 4 8 5
           6 3 6 8 3 1 4 6
           4 5 1 2 2 3 7 8];
end

matrixChangesdone = zeros(8);
for i = 1:8
    for j = 1 :8
        matrixChangesdone(i,j) = mat(row(i,j),col(i,j));
    end
end
