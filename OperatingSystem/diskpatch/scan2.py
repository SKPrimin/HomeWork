def scan(diskSet, needle):
    print(f"\nSCAN\n从{needle}号磁道开始")
    print(f"被访问的下一个磁道号\t移动距离（磁道数）")
    # 分割
    diskListBefore = [x for x in diskSet if x > needle]
    diskListAfter = [x for x in diskSet if x <= needle]
    # 将列表排序 前升序 后降序
    diskListBefore.sort()
    diskListAfter.sort(reverse=True)
    # 将后列表追加到前一列表
    diskListBefore.extend(diskListAfter)
    # 计算移动距离
    distanceSum = 0
    movdistan = []
    # 计算访问磁道号时的移动距离
    for item in diskListBefore:
        # 算出移动距离并保存
        movdistan.append(abs(needle - item))
        distanceSum += movdistan[-1]
        # 更新磁针位置
        needle = item
        print(f"\t{item}\t\t{movdistan[-1]}")
    print(f"\n总道数：{distanceSum}\t平均寻道长度：{distanceSum / len(movdistan)}")


def cscan(diskSet, needle):
    print(f"\nCSCAN\n从{needle}号磁道开始")
    print(f"被访问的下一个磁道号\t移动距离（磁道数）")
    # 分割
    diskListBefore = [x for x in diskSet if x > needle]
    diskListAfter = [x for x in diskSet if x <= needle]
    # 将列表排序 前升序 后降序
    diskListBefore.sort()
    diskListAfter.sort()
    # 将后列表追加到前一列表
    diskListBefore.extend(diskListAfter)
    # 计算移动距离
    distanceSum = 0
    movdistan = []
    # 计算访问磁道号时的移动距离
    for item in diskListBefore:
        # 算出移动距离并保存
        movdistan.append(abs(needle - item))
        distanceSum += movdistan[-1]
        # 更新磁针位置
        needle = item
        print(f"\t{item}\t\t{movdistan[-1]}")
    print(f"\n总道数：{distanceSum}\t平均寻道长度：{distanceSum / len(movdistan)}")


if __name__ == '__main__':
    track = [55, 58, 39, 18, 90, 160, 150, 38, 184]
    scan(track, 100)
    cscan(track, 100)
