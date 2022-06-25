# 最佳置换算法
def OPT(pageseq, blknum):
    blocks = []
    for i in range(blknum):
        blocks.append(pageseq[i])
        print(blocks, '缺页')
    misstm = blknum  # 缺页次数
    for i in range(blknum, len(pageseq)):
        if pageseq[i] not in blocks:  # 缺页
            pagemaxind = -1  # 初始化
            outpage = -1  # 初始化
            for b in blocks:
                if b not in pageseq[i:]:  # 在后续引用串中未找到该页面号
                    outpage = b  # 则应将该页面换出
                    break
                else:
                    pagemaxind = max(pagemaxind, pageseq.index(b, i))
                    outpage = pageseq[pagemaxind]  # 最长时间没被访问的页面
            blocks[blocks.index(outpage)] = pageseq[i]  # 置换
            misstm += 1
            print(blocks, '缺页，{}换出，{}换入'.format(outpage, pageseq[i]))
        else:  # 命中
            print(blocks)
    return misstm / len(pageseq)


# 先进先出置换算法
def FIFO(pageseq, blknum):
    blocks = []
    for i in range(blknum):
        blocks.append(pageseq[i])
        print(blocks, '缺页')
    misstm = blknum  # 缺页次数
    firstinp = 0  # 指向最先进来的页面
    for i in range(blknum, len(pageseq)):
        if pageseq[i] not in blocks:  # 缺页
            outpage = blocks[firstinp]
            blocks[firstinp] = pageseq[i]  # 置换
            print(blocks, '缺页，{}换出，{}换入'.format(outpage, pageseq[i]))
            firstinp = (firstinp + 1) % blknum
            misstm += 1
        else:  # 命中
            print(blocks)
    return misstm / len(pageseq)


# 最近最久未使用置换算法
def LRU(pageseq, blknum):
    blocks = []
    que = []  # 使用队列来找出LRU页面
    for i in range(blknum):
        blocks.append(pageseq[i])
        que.append(pageseq[i])
        print(blocks, '缺页')
    misstm = blknum  # 缺页次数
    for i in range(blknum, len(pageseq)):
        if pageseq[i] not in blocks:  # 缺页
            outpage = que.pop(0)  # 将队头弹出
            que.append(pageseq[i])  # 放到队尾
            blocks[blocks.index(outpage)] = pageseq[i]  # 置换
            print(blocks, '缺页，{}换出，{}换入'.format(outpage, pageseq[i]))
            misstm += 1
        else:  # 命中
            que.remove(pageseq[i])  # 将原来页面的弹出
            que.append(pageseq[i])  # 将新来的页面放到队尾
            print(blocks)
    return misstm / len(pageseq)


if __name__ == '__main__':
    pageseq = input('请输入页面号引用串（以空格分隔）：')
    # 7 0 1 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
    pageseq = list(map(lambda x: int(x), pageseq.split()))
    blknum = int(input('请输入物理块数：'))
    print('-----------------最佳置换算法------------------')
    OPT_missrate = OPT(pageseq, blknum)
    print('缺页率为：', OPT_missrate)
    print('----------------------------------------------')
    print('-----------------先进先出置换算法------------------')
    FIFO_missrate = FIFO(pageseq, blknum)
    print('缺页率为：', FIFO_missrate)
    print('--------------------------------------------------')
    print('-----------------最近最久未使用置换算法------------------')
    LRU_missrate = LRU(pageseq, blknum)
    print('缺页率为：', LRU_missrate)
    print('-------------------------------------------------------')
