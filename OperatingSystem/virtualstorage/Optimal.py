def optimal(pageNum, pageQueue):
    # 定义物理块,初始化缺页次数
    physicalBlock = []
    missingNum = 0
    for index, page in enumerate(pageQueue):
        # 查看本页是否在物理块中
        if page not in physicalBlock:
            # 缺页则再根据物理块情况判断
            missingNum += 1
            # 物理块充足时无需替换，直接加入物理块中
            if len(physicalBlock) < pageNum:
                physicalBlock.append(page)
                print(f"缺页{page}，无需置换，当前物理块{physicalBlock}")
            # 物理块不足时调用函数找出未来最远使用的一个
            else:
                farthest = findFarthest(pageQueue[index + 1:], physicalBlock)
                farIndex = physicalBlock.index(farthest)
                # 在物理块中替换
                physicalBlock[farIndex] = page
                print(f"缺页{page}，置换{farthest}元素，当前物理块{physicalBlock}")
        # 不缺页
        else:
            print(f"不缺页，{page}在物理块{physicalBlock}中")
    print("缺页率为{}/{} = {:.2%}".format(missingNum, len(pageQueue), missingNum / len(pageQueue)))


def findFarthest(alist, pblist):
    """找出物理块中最远使用的页面在物理块的索引以及页面号"""
    # 先默认要替换第一个页
    farthest = pblist[0]
    # 如果这个元素在后续列表中不存在，那么这是永远都用不到的，直接返回
    for item in pblist:
        if item not in alist:
            return item
    # index如果找不到会报错，故本处做处理，
    last = alist.index(pblist[0])
    # 遍历整个物理块
    for i in range(0, len(pblist)):
        # 如果这个元素比之前一个离得更远，就替换
        new = alist.index(pblist[i])
        if last < new:
            last = new
            farthest = pblist[i]
    return farthest


if __name__ == '__main__':
    # 设置分配的物理块数目
    # pageNum = int(input("请输入分配的物理块数目"))
    pageNum = 3
    # 接收输入的页面号引用串 并分割，int类型转换，转为列表
    # pageQueue = list(map(int, input("请输入页面号引用串").split()))
    pageQueue = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1]
    optimal(pageNum, pageQueue)
