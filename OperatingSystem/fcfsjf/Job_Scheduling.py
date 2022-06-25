"""实验一：分别设计FCFS和SJF算法来实现调度"""

count = int(input('请输入进程数目：'))
process = []


def inputprocess():
    i = 0
    while i < count:
        print('-------------------')
        process_name = input('请输入第{}个进程名：'.format(i+1))
        arrive_time = float(input('请输入达到时间：'))
        service_time = float(input('请输入服务时间：'))
        process.append([process_name, arrive_time, service_time, 0, 0, 0, 0])
        # 后面4个0分别表示开始执行完成、周转、带权周转时间
        i += 1


# 先进先服务调度算法
def FCFS():
    FPro = process[:]
    FPro.sort(key=lambda item: item[1])  # 按照达到时间从小到达排序
    # 首先计算第一个被调度的进程
    FPro[0][3] = FPro[0][1]  # 开始执行时间
    FPro[0][4] = FPro[0][1] + FPro[0][2]  # 完成时间
    FPro[0][5] = FPro[0][4] - FPro[0][1]  # 周转时间
    FPro[0][6] = FPro[0][5] / FPro[0][2]  # 带权周转时间
    for i in range(1, count):
        FPro[i][3] = max(FPro[i - 1][4], FPro[i][1])  # 开始执行时间
        FPro[i][4] = FPro[i][3] + FPro[i][2]  # 完成时间
        FPro[i][5] = FPro[i][4] - FPro[i][1]  # 周转时间
        FPro[i][6] = FPro[i][5] / FPro[i][2]  # 带权周转时间
    aver_TAT = 0
    aver_WTAT = 0
    for i in range(count):
        aver_TAT += FPro[i][5]
        aver_WTAT += FPro[i][6]
    aver_TAT /= count  # 平均周转时间
    aver_WTAT /= count  # 平均带权周转时间
    # 输出
    print('FCFS算法计算结果：')
    for pro in FPro:
        print('{0[0]}进程在时刻{0[1]}到来，服务时间为{0[2]},开始执行时间为{0[3]},完成时间为{0[4]},周转时间为{0[5]},带权周转时间为{0[6]}'.format(pro))
    print('本次调度的平均周转时间为{0}，平均带权周转时间为{1}'.format(aver_TAT, aver_WTAT))


# 短进程优先调度算法
def SJF():
    SPro = process[:]
    SPro.sort(key=lambda item: (item[1]))  # 先按照到达时间时间排序
    SPro[1:] = sorted(SPro[1:], key=lambda item: (item[2]))  # 后面的进程按照服务时间排序
    # 首先计算第一个被调度的进程
    SPro[0][3] = SPro[0][1]  # 开始执行时间
    SPro[0][4] = SPro[0][1] + SPro[0][2]  # 完成时间
    SPro[0][5] = SPro[0][4] - SPro[0][1]  # 周转时间
    SPro[0][6] = SPro[0][5] / SPro[0][2]  # 带权周转时间
    nowtime = SPro[0][4]  # 当前完成时间
    i = 1
    while i < count:
        tem_pro = []
        pre_pro = SPro[:]
        min_arrive = min(SPro[i:], key=lambda item: item[1])  # 找出最小到达时间
        if min_arrive[1] > nowtime:  # 如果最小到达时间小于当前完成时间
            k = SPro.index(min_arrive)
            # 调度该进程
            SPro[k][3] = max(nowtime, SPro[k][1])  # 开始执行时间
            SPro[k][4] = SPro[k][3] + SPro[k][2]  # 完成时间
            SPro[k][5] = SPro[k][4] - SPro[k][1]  # 周转时间
            SPro[k][6] = SPro[k][5] / SPro[k][2]  # 带权周转时间
            nowtime = SPro[k][4]  # 更新当前完成时间
            SPro[i], SPro[k] = SPro[k], SPro[i]
            SPro[i + 1:] = sorted(SPro[i + 1:], key=lambda item: (item[2]))  # 后面的进程按照服务时间排序
            i += 1
        j = i
        if j >= count:
            break
        while pre_pro[j][1] > nowtime:
            tem_pro.append(pre_pro[j])
            SPro.pop(i)  # 将还未到达的进程弹出
            j += 1
            if j >= count:  # 所有进程均未达到，则重新排序
                tem_pro.sort(key=lambda item: (item[1]))  # 先按照到达时间时间排序
                tem_pro[1:] = sorted(tem_pro[1:], key=lambda item: (item[2]))  # 后面的进程按照服务时间排序
                break
        else:  # 到达时间小于当前完成时间，则调度该进程
            SPro[i][3] = max(nowtime, SPro[i][1])  # 开始执行时间
            SPro[i][4] = SPro[i][3] + SPro[i][2]  # 完成时间
            SPro[i][5] = SPro[i][4] - SPro[i][1]  # 周转时间
            SPro[i][6] = SPro[i][5] / SPro[i][2]  # 带权周转时间
            nowtime = SPro[i][4]  # 更新当前完成时间
            i += 1
        SPro = SPro[:i] + tem_pro + SPro[i:]  # 插入之前未达到的进程
    aver_TAT = 0
    aver_WTAT = 0
    for i in range(count):
        aver_TAT += SPro[i][5]
        aver_WTAT += SPro[i][6]
    aver_TAT /= count  # 平均周转时间
    aver_WTAT /= count  # 平均带权周转时间
    # 输出
    SPro.sort(key=lambda item: (item[1]))  # 按照到达时间时间输出
    print('SJF算法计算结果：')
    for pro in SPro:
        print('{0[0]}进程在时刻{0[1]}到来，服务时间为{0[2]},开始执行时间为{0[3]},完成时间为{0[4]},周转时间为{0[5]},带权周转时间为{0[6]}'.format(pro))
    print('本次调度的平均周转时间为{0}，平均带权周转时间为{1}'.format(aver_TAT, aver_WTAT))


if __name__ == '__main__':
    inputprocess()
    print('-------------------')
    FCFS()
    print('-------------------')
    SJF()
