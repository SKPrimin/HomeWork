package com.process.fcfs;

import java.text.DecimalFormat;

/**
 * @author: SKPrimin E01914168张丞
 * @date: 2021/10/28  19:18
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
     * 四个私有变量：开始执行时间、完成时间、周转时间、带权周转时间
     */
    private int timeStart;
    private int timeComplete;
    private int timeTurnaround;
    private double timeWeightedTurnaround;

    public PCB() {//允许空参构造器存在
    }

    public PCB(String threadName, int timeArrival, int timeSever) { //正规的有参构造器
        this.threadName = threadName;
        this.timeArrival = timeArrival;
        this.timeSever = timeSever;
    }

    public void setTimeStart(int timeStart) {//将由算法调度程序分配开始时间
        this.timeStart = timeStart;
    }

    public int getTimeComplete() {
        return timeComplete;
    }

    public int getTimeTurnaround() {
        return timeTurnaround;
    }

    public double getTimeWeightedTurnaround() {
        return timeWeightedTurnaround;
    }

    public void run() { //开始调度后的运行内容
        /* 计算出完成时间、周转时间、带权周转时间 */
        timeComplete = timeStart + timeSever;
        timeTurnaround = timeComplete - timeArrival;
        DecimalFormat dF = new DecimalFormat("0.00");
        timeWeightedTurnaround = Double.parseDouble(dF.format((double) timeTurnaround / timeSever));
        //调用toString()将内容输出
        System.out.println(this);

    }

    @Override
    public String toString() {
        return "'" + threadName + '\'' +
                "\t\t" + timeArrival +
                "\t\t" + timeSever +
                "\t\t\t" + timeStart +
                "\t\t" + timeComplete +
                "\t\t" + timeTurnaround +
                "\t\t" + timeWeightedTurnaround;
    }
}
