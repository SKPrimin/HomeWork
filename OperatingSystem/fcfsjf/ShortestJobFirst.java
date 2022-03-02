package com.process.fcfs;

/**
 * @author: SKPrimin E01914168张丞
 * @date: 2021/10/28  19:50
 * @ClassName: ShortestJobFirst
 * @Description: TODO 短作业优先算法
 */
public class ShortestJobFirst {
    public void dispatch(PCB[] starr) {
        System.out.println("短作业优先算法算法");
        System.out.println("作业名\t到达时间\t服务时间\t开始执行时间\t完成时间\t周转时间\t带权周转时间");
        int num = starr.length;
        //周转时间之和与带权周转时间之和
        int timeTurnaroundSum = 0;
        double timeWeightedTurnaroundSum = 0;
        sort(starr, num);
        //此后的SeverThread数组都是依照服务时间排序完成的
        /* 当前执行进程、系统调度此次作业的时间、调度完成的作业数目*/
        PCB item = starr[0];
        int timeStart = starr[0].timeArrival;
        int count = 0;
        boolean lastsortflag = true;
        for (int i = 0; i < num; i++) {

            // 三元运算符，确保系统调度作业时作业已经到达
            timeStart = timeStart > item.timeArrival ? timeStart : item.timeArrival;
            item.setTimeStart(timeStart);
            item.run();
            //完成作业+1,并在将此次完成时间作为下一个已到达作业的开始时间
            count++;
            timeStart = item.getTimeComplete();
            timeTurnaroundSum += item.getTimeTurnaround();
            timeWeightedTurnaroundSum += item.getTimeWeightedTurnaround();
            //已到达的作业再依照服务时间重排，先确立左右边界
            int rightcount = count;
            for (int j = 0; j < num - count; j++) {
                if (starr[j + count].timeArrival <= timeStart) {
                    rightcount++;
                }
            }
            // 需要重排的数组切片，当所有作业都重排后停止
            if (rightcount <= num && lastsortflag){
                sortSevertime(starr, count, rightcount);
            }
            if (rightcount  == num){ // 代表已经将所有作业重排，此后无需重排
                lastsortflag = false;
            }
            item = starr[(i + 1) % num];
        }
        System.out.println("平均周转时间：" + (double) timeTurnaroundSum / num +
                "，平均带权周转时间：" + timeWeightedTurnaroundSum / num);
    }

    public void sort(PCB[] starr, int num) {
        //根据到达时间对作业进行升序排序，排序方式：选择排序
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

    public void sortSevertime(PCB[] starr, int left, int right) {
        //根据服务时间对作业进行升序排序，排序方式：选择排序
        int num = right - left;
        for (int i = 0; i < num - 1; i++) {
            int index = i;
            for (int j = i + 1; j < num; j++) {
                if (starr[left + j].timeSever < starr[left + index].timeSever) {
                    index = j;
                }
            }
            //将找到的最小值放到第一的位置，进行下一遍循环
            PCB temp = starr[left + index];
            starr[left + index] = starr[left + i];
            starr[left + i] = temp;
        }
    }

}
