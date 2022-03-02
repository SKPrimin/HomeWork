def fifo(pageNum, pageQueue):
    # 定义物理块,初始化缺页次数
    physicalBlock = []
    missingNum = 0
    # 时间记录表，记录物理块中各元素进入时间
    enterTime = []
    for index, page in enumerate(pageQueue):
        # 查看是否缺页
        if page not in physicalBlock:
            # 缺页则再根据物理块情况判断
            missingNum += 1
            # 物理块充足时无需替换，直接加入物理块中，并记录进入时间
            if len(physicalBlock) < pageNum:
                physicalBlock.append(page)
                enterTime.append(index)
                print(f"缺页{page}，无需置换，当前物理块{physicalBlock}")
            # 物理块不足时调用函数找出内存驻留时间最长的页面，即在enterTime值最小
            else:
                # 找到存在时间最长的元素
                longestTime = min(enterTime)
                # 获取要替换位置的索引
                timeIndex = enterTime.index(longestTime)
                longest = physicalBlock[timeIndex]
                # 根据索引进行替换，时间表物理块都进行替换
                physicalBlock[timeIndex] = page
                enterTime[timeIndex] = index
                print(f"缺页{page}，置换{longest}元素，当前物理块{physicalBlock}")
        # 不缺页
        else:
            print(f"不缺页，{page}在物理块{physicalBlock}中")
    print("缺页率为{}/{} = {:.2%}".format(missingNum, len(pageQueue), missingNum / len(pageQueue)))


if __name__ == '__main__':
    # 设置分配的物理块数目
    # pageNum = int(input("请输入分配的物理块数目"))
    pageNum = 3
    # 接收输入的页面号引用串 并分割，int类型转换，转为列表
    # pageQueue = list(map(int, input("请输入页面号引用串").split()))
    pageQueue = [7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1]
    fifo(pageNum, pageQueue)