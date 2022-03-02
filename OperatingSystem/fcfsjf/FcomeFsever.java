package com.process.fcfs;

/**
 * @author: SKPrimin E01914168张丞
 * @date: 2021/10/28  19:10
 * @ClassName: FCFS
 * @Description: TODO 先来先服务算法
 */
public class FcomeFsever {
    public void dispatch(PCB[] starr) {
        System.out.println("先来先服务算法");
        System.out.println("作业名\t到达时间\t服务时间\t开始执行时间\t完成时间\t周转时间\t带权周转时间");
        int num = starr.length;
        //周转时间之和与带权周转时间之和
        int timeTurnaroundSum = 0;
        double timeWeightedTurnaroundSum = 0;
        sort(starr, num);
        //此后的SeverThread数组都是排序完成的
        int timeStart = starr[0].timeArrival;
        for (PCB i : starr) {
            // 三元运算符，确保系统调度作业时作业已经到达
            timeStart = timeStart > i.timeArrival ? timeStart : i.timeArrival;
            i.setTimeStart(timeStart);
            i.run();
            // 将此次完成时间作为下一个已到达作业的开始时间
            timeStart = i.getTimeComplete();
            timeTurnaroundSum += i.getTimeTurnaround();
            timeWeightedTurnaroundSum += i.getTimeWeightedTurnaround();
        }
        System.out.println("平均周转时间："+(double)timeTurnaroundSum/num+
                "，平均带权周转时间："+ timeWeightedTurnaroundSum /num);
    }

    public void sort(PCB[] starr, int num) { //根据到达时间对作业进行升序排序，排序方式：选择排序
        for (int i = 0; i < num - 1; i++) {
            int index = i;
            for (int j = i + 1; j < num; j++) {
                if (starr[j].timeArrival < starr[index].timeArrival) {
                    index = j;
                }
            }
            //将找到的最小值放到第一的位置，进行下一遍循环
            PCB temp = starr[index];
            starr[index] = starr[i];
            starr[i] = temp;
        }
    }
}
