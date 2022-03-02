package com.process.rr;


/**
 * @author: SKPrimin E01914168 张丞
 * @date: 2021/11/11  19:07
 * @ClassName: RR
 * @Description: TODO 时间片轮转算法
 */
public class RR {
    public void dispatch(PCB[] pcbarr, int timeSlice) {
        System.out.println("作业名\t到达时间\t服务时间\t开始执行时间\t完成时间\t周转时间\t带权周转时间");
        int num = pcbarr.length;

        sort(pcbarr, num);
        //此后的PCB数组都是依照到达时间排序完成的
        //由主机记录当前时间，以便实现时间片轮转,初始值为第一个元素
        int timeNow = pcbarr[0].timeArrival;
        int countFinish = 0;
        while (countFinish < num) {
            countFinish = 0;
            for (PCB pcb : pcbarr) {
                //如果此进程未完成，且时间已到达，则会给该进程一个时间片,否则进行下一个
                if (timeNow >= pcb.timeArrival) {
                    if ((!pcb.isFinish())) {
                        if (pcb.isNotStart()) {
                            pcb.setTimeStart(timeNow);
                        }
                        pcb.run(timeNow, timeSlice);
                        timeNow += pcb.getTimeUse();
                    } else {
                        countFinish++;
                    }
                }else{//若还未到，则直接当前时间加一，从下一轮开始
                    timeNow++;
                    break;
                }
            }
        }
        //周转时间之和与带权周转时间之和
        int timeTurnaroundSum = 0;
        double timeWeightedTurnaroundSum = 0;
        for (PCB pcb : pcbarr) {
            timeTurnaroundSum += pcb.getTimeTurnaround();
            timeWeightedTurnaroundSum += pcb.getTimeWeightedTurnaround();
        }
        System.out.println("平均周转时间：" + (double) timeTurnaroundSum / num +
                "，平均带权周转时间：" + timeWeightedTurnaroundSum / num);

    }

    public void sort(PCB[] arr, int num) {
        //根据到达时间对作业进行升序排序，排序方式：选择排序
        for (int i = 0; i < num - 1; i++) {
            int index = i;
            for (int j = i + 1; j < num; j++) {
                if (arr[j].timeArrival < arr[index].timeArrival) {
                    index = j;
                }
            }
            //将找到的最小值放到第一的位置，进行下一遍循环
            PCB temp = arr[index];
            arr[index] = arr[i];
            arr[i] = temp;
        }
    }
}
