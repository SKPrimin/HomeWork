import copy


# 扫描算法
def SCAN(seq, start, drct):
    tempseq = copy.deepcopy(seq)
    distance = 0
    nownum = start
    if drct == 0:
        tempseq.sort()
        i = 0
        for i in range(len(tempseq)):
            if tempseq[i] >= start:
                break
        templist = list(reversed(tempseq[:i]))
        tempseq = tempseq[i:] + templist
        for num in tempseq:
            d = abs(nownum - num)
            distance += d
            nownum = num
            print('被访问的下一个磁道号：{}  \t移动距离：{}'.format(num, d))
        return distance / len(seq)
    else:
        tempseq.sort(reverse=True)
        i = 0
        for i in range(len(tempseq)):
            if tempseq[i] <= start:
                break
        templist = list(reversed(tempseq[:i]))
        tempseq = tempseq[i:] + templist
        for num in tempseq:
            d = abs(nownum - num)
            distance += d
            nownum = num
            print('被访问的下一个磁道号：{}  \t移动距离：{}'.format(num, d))
        return distance / len(seq)


# 循环扫描算法
def CSCAN(seq, start, drct):
    tempseq = copy.deepcopy(seq)
    distance = 0
    nownum = start
    if drct == 0:
        tempseq.sort()
        i = 0
        for i in range(len(tempseq)):
            if tempseq[i] >= start:
                break
        tempseq = tempseq[i:] + tempseq[:i]
        for num in tempseq:
            d = abs(nownum - num)
            distance += d
            nownum = num
            print('被访问的下一个磁道号：{}  \t移动距离：{}'.format(num, d))
        return distance / len(seq)
    else:
        tempseq.sort(reverse=True)
        i = 0
        for i in range(len(tempseq)):
            if tempseq[i] <= start:
                break
        tempseq = tempseq[i:] + tempseq[:i]
        for num in tempseq:
            d = abs(nownum - num)
            distance += d
            nownum = num
            print('被访问的下一个磁道号：{}  \t移动距离：{}'.format(num, d))
        return distance / len(seq)


if __name__ == '__main__':
    diskseq = input('请输入需要访问的磁道号序列（以空格分隔）：')
    # 55 58 39 18 90 160 150 38 184
    diskseq = list(map(lambda x: int(x), diskseq.split()))
    startnum = int(input('请输入当前磁头所在的磁道号：'))
    direction = int(input('请输入当前磁头移动的方向（0表示自里向外，1表示自外向里）：'))
    print('-----------------扫描算法--------------------')
    average_SCAN = SCAN(diskseq, startnum, direction)
    print('平均寻道长度：', average_SCAN)
    print('--------------------------------------------')
    print('-----------------循环扫描算法--------------------')
    average_CSCAN = CSCAN(diskseq, startnum, direction)
    print('平均寻道长度：', average_CSCAN)
    print('------------------------------------------------')
