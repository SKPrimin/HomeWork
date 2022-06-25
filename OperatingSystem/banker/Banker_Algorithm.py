import copy

print('E01914271 梁意')


# 需要的是否小于可分配的
def NeedLessWork(nd, wk):
    for i in range(len(wk)):
        if nd[i] > wk[i]:
            return False  # 只要要一个资源不满足则返回False
    return True


# 判断是否已经分配结束
def isFinish(finish):
    for fns in finish:
        if not fns:
            return False  # 只要有一个还未分配则表示未分配结束
    return True


# 读取资源分配表文件的信息
def getinf(filename):
    allocation = []  # 分配矩阵
    need = []  # 需求矩阵
    Max = []  # 最大需求矩阵
    with open(filename, 'r', encoding='utf-8') as fp:
        lines = fp.readlines()
        num=lines[0].strip()
        pronum=int(num[0])
        rscnum=int(num[2])
        for i in range(1, pronum + 1):
            p = lines[i].strip()  # 去掉换行符
            p = list(map(lambda x: int(x), p.split()))
            allocation.append(p[:rscnum])
            need.append(p[rscnum:])  # 前半部分是已分配资源，后半部分是还需资源
            maxi = list(map(lambda x, y: x + y, p[:rscnum], p[rscnum:]))
            Max.append(maxi)
        available = lines[len(lines) - 1].strip()  # 去掉换行符
        available = list(map(lambda x: int(x), available.split()))  # 可用资源
        return Max, allocation, need, available


# 输出当前的资源分配情况
def printrsc(Max, allocation, need, available):
    print('-------------当前的资源分配情况如下：----------------')
    print('\t\t\tMax\t\t\tAllocation\t\t\tNeed\t\tAvailable')
    print('P0\t\t{}\t\t{}\t\t{}\t\t{}'.format(Max[0], allocation[0], need[0], available))
    for i in range(1, len(Max)):
        print('P{}\t\t{}\t\t{}\t\t{}'.format(i, Max[i], allocation[i], need[i]))
    print('----------------------------------------------------')


# 安全性算法
def safe_alg(need, allocation, available):
    work = copy.deepcopy(available)
    finish = [False] * len(need)
    safe = []  # 存放安全序列
    while not isFinish(finish):
        i = 0
        for i in range(len(need)):
            if not finish[i] and NeedLessWork(need[i], work):
                work = list(map(lambda x, y: x + y, allocation[i], work))  # 分配资源后回收资源
                finish[i] = True
                safe.append(i)
                i = 0  # 从头开始找可以分配资源的进程
                break
        if i == len(need):
            break  # 已经找不到可以分配资源的进程了
    if isFinish(finish):
        return safe
    else:
        return False  # 未找到安全序列


# 银行家算法
def banker_alg(p, rqst, need, allocation, available):
    if not NeedLessWork(rqst, need[p]) or not NeedLessWork(rqst, available):
        return False
    tempneed = copy.deepcopy(need)
    tempalloc = copy.deepcopy(allocation)
    # 假定给进程分配资源
    work = list(map(lambda x, y: x - y, available, rqst))
    tempneed[p] = list(map(lambda x, y: x - y, tempneed[p], rqst))
    tempalloc[p] = list(map(lambda x, y: x + y, tempalloc[p], rqst))
    seq = safe_alg(tempneed, tempalloc, work)
    if not seq:
        return False
    else:
        return seq


# 主函数
def main():
    filename = 'RAT.txt'
    Max, allocation, need, available = getinf(filename)
    printrsc(Max, allocation, need, available)
    seq = safe_alg(need, allocation, available)
    if seq:
        print('当前状态的安全序列为：', end='')
        for i in seq:
            print('P' + str(i), end=' ')
    else:
        print('该状态不安全！')
        return
    while True:
        print()
        p = input('\n请输入申请资源的进程序号（输入的不是自然数则退出）：')
        if p.isdigit():
            p = int(p)
        else:
            print('已退出！')
            return
        request = input('请输入该进程的请求资源向量（空格分隔）：')
        request = list(map(lambda x: int(x), request.split()))
        seq = banker_alg(p, request, need, allocation, available)
        if seq:
            print('可将资源分配给该进程，分配后：')
            need[p] = list(map(lambda x, y: x - y, need[p], request))
            allocation[p] = list(map(lambda x, y: x + y, allocation[p], request))
            available = list(map(lambda x, y: x - y, available, request))
            M = []
            for i in range(len(need)):
                maxi = list(map(lambda x, y: x + y, need[i], allocation[i]))
                M.append(maxi)
            printrsc(M, allocation, need, available)
            print('当前状态的安全序列为：', end='')
            for i in seq:
                print('P' + str(i), end=' ')
        else:
            print('不能将资源分配给该进程！')
            return


if __name__ == '__main__':
    main()
