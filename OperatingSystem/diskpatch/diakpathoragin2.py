def fifo(tracklist, needle):
    movdistan = []
    distanceSum = 0
    print(f"\n先来先服务FCFS\n从{needle}号磁道开始")
    print(f"被访问的下一个磁道号\t移动距离（磁道数）")
    for index, item in enumerate(tracklist):
        # 算出移动距离并保存
        movdistan.append(abs(needle - item))
        distanceSum += movdistan[-1]
        # 更新磁针位置
        needle = item
        print(f"\t{item}\t\t\t\t\t{movdistan[-1]}")
    print(f"\n总道数：{distanceSum}\t平均寻道长度：{distanceSum / len(movdistan)}")
    return movdistan, distanceSum


def sstf(tracklist, needle):
    movdistan = []
    trackSequence = []
    distanceSum = 0
    print(f"\n最短寻道时间优先SSTF\n从{needle}号磁道开始")
    print(f"被访问的下一个磁道号\t移动距离（磁道数）")
    length = len(tracklist)
    for i in range(length):
        # 求出移动距离的磁道号以及移动距离
        ts, distance = shortest(tracklist,needle )
        trackSequence.append(ts)
        movdistan.append(distance)
        # 将算出的将要访问的下一磁道号、移动距离加入对应数组
        distanceSum += distance
        # 更新指针位置以及磁道号列表，去除已经访问的磁道号
        needle = ts
        tracklist.remove(ts)
        print(f"\t{ts}\t\t\t\t\t{distance}")
    print(f"\n总道数：{distanceSum}\t平均寻道长度：{distanceSum / len(movdistan)}")



def shortest(array,needle):
    # 各变量初始化 先默认第一个是距离最近的磁道
    diskName = array[0]
    distance = abs(needle - array[0])
    # 进过遍历，若发现有离得更近的就替换
    for item in array:
        if abs(needle - item) < distance:
            diskName = item
            distance = abs(needle - item)
    return diskName, distance

if __name__ == '__main__':

    track = [55, 58, 39, 18, 90, 160, 150, 38, 184]
    fifo(track, 100)
    sstf(track, 100)
