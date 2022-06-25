import copy



# 先来先服务
def FCFS(seq, start):
    distance = 0
    nownum = start
    for num in seq:
        d = abs(nownum - num)
        distance += d
        nownum = num
        print('被访问的下一个磁道号：{}  \t移动距离：{}'.format(num, d))
    return distance / len(seq)


# 最短寻道时间优先
def SSTF(seq, start):
    distance = 0
    nownum = start
    tempseq = copy.deepcopy(seq)
    for i in range(len(seq)):
        tempseq.sort(key=lambda x: abs(x - nownum))
        num = tempseq.pop(0)  # 第一个元素是离当前磁头最近磁道号
        d = abs(nownum - num)  # 离当前磁头最近的距离
        distance += d
        nownum = num
        print('被访问的下一个磁道号：{}  \t移动距离：{}'.format(num, d))
    return distance / len(seq)


if __name__ == '__main__':
    diskseq = input('请输入需要访问的磁道号序列（以空格分隔）：')
    # 55 58 39 18 90 160 150 38 184
    diskseq = list(map(lambda x: int(x), diskseq.split()))
    startnum = int(input('请输入当前磁头所在的磁道号：'))
    print('-----------------先来先服务--------------------')
    average_FCFS = FCFS(diskseq, startnum)
    print('平均寻道长度：', average_FCFS)
    print('----------------------------------------------')
    print('-----------------最短寻道时间优先--------------------')
    average_SSTF = SSTF(diskseq, startnum)
    print('平均寻道长度：', average_SSTF)
    print('----------------------------------------------------')
