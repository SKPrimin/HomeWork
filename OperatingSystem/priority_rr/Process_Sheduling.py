"""实验二：分别设计非抢占式静态优先权调度算法和时间片轮转算法来实现调度"""
import copy
from queue import Queue

count = int(input('请输入进程数目：'))
process = []


# 输入进程相关信息
def inputprocess():
    i = 0
    while i < count:
        print('-------------------')
        process_name = input('请输入第%d个进程名：' % (i + 1))
        arrive_time = float(input('请输入达到时间：'))
        service_time = float(input('请输入服务时间：'))
        priority = int(input('请输入优先数：'))
        process.append([process_name, arrive_time, service_time, priority, 0, 0, 0])
        # 后面3个0分别表示完成、周转、带权周转时间
        i += 1


# 非抢占式静态优先权调度算法
def PS():
    PPro = process[:]
    PPro.sort(key=lambda item: (item[1]))  # 先按照到达时间时间排序
    PPro[1:] = sorted(PPro[1:], key=lambda item: (item[3]))  # 后面的进程按照优先级排序
    # 首先计算第一个被调度的进 程
    start = PPro[0][1]  # 开始执行时间
    PPro[0][4] = PPro[0][1] + PPro[0][2]  # 完成时间
    PPro[0][5] = PPro[0][4] - PPro[0][1]  # 周转时间
    PPro[0][6] = PPro[0][5] / PPro[0][2]  # 带权周转时间
    nowtime = PPro[0][4]  # 当前完成时间
    i = 1
    while i < count:
        tem_pro = []
        pre_pro = PPro[:]
        min_arrive = min(PPro[i:], key=lambda item: item[1])  # 找出最小到达时间
        if min_arrive[1] > nowtime:  # 如果最小到达时间小于当前完成时间
            k = PPro.index(min_arrive)
            # 调度该进程
            start = max(nowtime, PPro[k][1])  # 开始执行时间
            PPro[k][4] = start + PPro[k][2]  # 完成时间
            PPro[k][5] = PPro[k][4] - PPro[k][1]  # 周转时间
            PPro[k][6] = PPro[k][5] / PPro[k][2]  # 带权周转时间
            nowtime = PPro[k][4]  # 更新当前完成时间
            PPro[i], PPro[k] = PPro[k], PPro[i]
            PPro[i + 1:] = sorted(PPro[i + 1:], key=lambda item: (item[3]))  # 后面的进程按照优先级排序
            i += 1
        j = i
        if j >= count:
            break
        while pre_pro[j][1] > nowtime:
            tem_pro.append(pre_pro[j])
            PPro.pop(i)  # 将还未到达的进程弹出
            j += 1
            if j >= count:  # 所有进程均未达到，则重新排序
                tem_pro.sort(key=lambda item: (item[1]))  # 先按照到达时间时间排序
                tem_pro[1:] = sorted(tem_pro[1:], key=lambda item: (item[3]))  # 后面的进程按照优先级排序
                break
        else:  # 到达时间小于当前完成时间，则调度该进程
            start = max(nowtime, PPro[i][1])  # 开始执行时间
            PPro[i][4] = start + PPro[i][2]  # 完成时间
            PPro[i][5] = PPro[i][4] - PPro[i][1]  # 周转时间
            PPro[i][6] = PPro[i][5] / PPro[i][2]  # 带权周转时间
            nowtime = PPro[i][4]  # 更新当前完成时间
            i += 1
        PPro = PPro[:i] + tem_pro + PPro[i:]  # 插入之前未达到的进程
    aver_TAT = 0
    aver_WTAT = 0
    for i in range(count):
        aver_TAT += PPro[i][5]
        aver_WTAT += PPro[i][6]
    aver_TAT /= count  # 平均周转时间
    aver_WTAT /= count  # 平均带权周转时间
    # 输出
    PPro.sort(key=lambda item: (item[1]))  # 按照到达时间时间输出
    print('非抢占式静态优先权调度算法计算结果：')
    for pro in PPro:
        print('{0[0]}进程在时刻{0[1]}到来，服务时间为{0[2]},优先级为{0[3]},完成时间为{0[4]},周转时间为{0[5]},带权周转时间为{0[6]}'.format(pro))
    print('本次调度的平均周转时间为{0}，平均带权周转时间为{1}'.format(aver_TAT, aver_WTAT))


# 时间片轮转调度算法
def RRS(rr):
    RPro = process[:]
    RPro.sort(key=lambda item: item[1])  # 按照达到时间从小到大排序
    temppro = copy.deepcopy(RPro)
    qu = Queue()
    nowP = temppro[0]
    if nowP[2] > rr:  # 服务时间大于时间片
        nowP[2] -= rr  # 还需要服务的时间
        nowtime = nowP[1] + rr  # 当前完成时间
    else:  # 服务时间小于等于时间片
        nowP[4] = nowP[1] + nowP[2]  # 完成时间
        nowP[5] = nowP[4] - nowP[1]
        nowP[6] = nowP[5] / nowP[2]
        nowtime = nowP[1] + nowP[2]  # 当前完成时间
        nowP[2] = 0  # 服务结束
    if nowP[2] > 0:  # 服务未结束，放到队尾
        qu.put(nowP)
    i = 0
    flag = 1
    while flag:
        if i >= count - 1:  # 所有进程均已达到
            nowP = qu.get()
        else:
            if temppro[i + 1][1] <= nowtime:  # 下一个进程已经到达
                nowP = temppro[i + 1]  # 调度最新到来的进程
                i += 1
            else:  # 下一个进程还未到达
                if not qu.empty():  # 队列非空
                    nowP = qu.get()  # 调度当前队头进程
                else:  # 队列已空
                    nowP = temppro[i + 1]
                    nowtime = nowP[1]
                    i += 1
        if nowP[2] > rr:  # 服务时间大于时间片
            nowP[2] -= rr  # 还需要服务的时间
            nowtime = nowtime + rr  # 当前完成时间
        else:  # 服务时间小于等于时间片
            ind = temppro.index(nowP)  # 获得该进程的索引
            servicetime = RPro[ind][2]  # 原始的服务时间
            nowP[4] = nowtime + nowP[2]  # 完成时间
            nowP[5] = nowP[4] - nowP[1]
            nowP[6] = nowP[5] / servicetime
            nowtime = nowP[4]  # 更新当前完成时间
            nowP[2] = 0  # 服务结束
        if nowP[2] > 0:  # 服务未结束，放到队尾
            qu.put(nowP)
        for j in range(count):
            if temppro[j][2] == 0:
                flag = 0
            else:
                flag = 1  # 还有未服务结束的进程
                break
    for i in range(count):
        RPro[i][4] = temppro[i][4]
        RPro[i][5] = temppro[i][5]
        RPro[i][6] = temppro[i][6]
    aver_TAT = 0
    aver_WTAT = 0
    for i in range(count):
        aver_TAT += RPro[i][5]
        aver_WTAT += RPro[i][6]
    aver_TAT /= count  # 平均周转时间
    aver_WTAT /= count  # 平均带权周转时间
    # 输出
    RPro.sort(key=lambda item: (item[1]))  # 按照到达时间时间输出
    print('时间片轮转调度算法计算结果：')
    for pro in RPro:
        print('{0[0]}进程在时刻{0[1]}到来，服务时间为{0[2]},优先级为{0[3]},完成时间为{0[4]},周转时间为{0[5]},带权周转时间为{0[6]}'.format(pro))
    print('本次调度的平均周转时间为{0}，平均带权周转时间为{1}'.format(aver_TAT, aver_WTAT))


if __name__ == '__main__':
    inputprocess()
    print('-------------------')
    PS()
    print('-------------------')
    rr = int(input('下面将使用时间片轮转调度算法，请输入时间片大小：'))
    RRS(rr)
