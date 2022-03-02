package com.process.rr;

import java.text.DecimalFormat;

/**
 * @author: SKPrimin E01914168张丞
 * @date: 2021/11/11  19:07
 * @ClassName: SeverThread
 * @Description: TODO 定义一个作业类，模拟PCB
 */
public class PCB {
    /**
     * 三个公共变量:作业名、到达时间、服务时间
     */
    String threadName;
    int timeArrival;
    int timeSever;

    /**
     * 五个私有变量：计算专用服务时间、开始执行时间、完成时间、周转时间、带权周转时间
     * 一个标志：表示是否还需要调度
     * 一个交互式变量：表示自己本次使用了多少时间
     */
    private int timeSeverFor;
    private int timeStart;
    private int timeComplete;
    private int timeTurnaround;
    private double timeWeightedTurnaround;
    private boolean isFinish = false;
    private int timeUse;

    public PCB() {//允许空参构造器存在
    }

    public PCB(String threadName, int timeArrival, int timeSever) { //正规的有参构造器
        this.threadName = threadName;
        this.timeArrival = timeArrival;
        this.timeSever = timeSever;
        this.timeSeverFor = timeSever;
    }

    public void setTimeStart(int timeStart) {//将由算法调度程序分配开始时间
        this.timeStart = timeStart;
    }

    public boolean isNotStart() {
        return timeStart == 0;
    }

    public int getTimeTurnaround() {
        return timeTurnaround;
    }

    public double getTimeWeightedTurnaround() {
        return timeWeightedTurnaround;
    }

    public boolean isFinish() {
        return isFinish;
    }

    public int getTimeUse() {
        return timeUse;
    }

    public void run(int timeNow, int timeSlice) { //开始调度后的运行内容
        /*计算完成时间*/
        if (timeSever > 0) {
            timeSever -= timeSlice;
            // 此处保证进程在时间片内提前完成的情况下，依然能准确算出完成时间，并返回正确的使用时间
            timeComplete = timeSever > 0 ? timeNow + timeSlice : timeNow + timeSlice + timeSever;
            timeUse = timeSever >= 0 ? timeSlice : timeSlice + timeSever;
        }
        /* 当本次进程完成时，计算周转时间、带权周转时间 */
        if (timeSever <= 0) {
            isFinish = true;
            timeTurnaround = timeComplete - timeArrival;
            DecimalFormat dF = new DecimalFormat("0.00");
            timeWeightedTurnaround = Double.parseDouble(dF.format((double) timeTurnaround / timeSeverFor));
            //调用toString()将内容输出
            System.out.println(this);
        }

    }

    @Override
    public String toString() {
        return "'" + threadName + '\'' +
                "\t\t" + timeArrival +
                "\t\t" + timeSeverFor +
                "\t\t\t" + timeStart +
                "\t\t" + timeComplete +
                "\t\t" + timeTurnaround +
                "\t\t" + timeWeightedTurnaround;
    }
}
