package com.process.priority;

import java.util.Scanner;

/**
 * @author: SKPrimin E01914168 张丞
 * @date: 2021/11/18  17:59
 * @ClassName: Test
 * @Description: TODO
 */
public class Test {
    public static void main(String[] args) {
        // 读取输入的数组
        PCB[] arr1 = dataReadIn();

        //调用两大算法
        NPPS fcfs = new NPPS();
        fcfs.dispatch(arr1);
    }

    public static PCB[] dataReadIn() { //数据读入函数,直接设为静态函数，强制要求写入数据
        System.out.print("请输入本次需要调度的作业数目：");
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        PCB[] starr = new PCB[n];
        System.out.println("请输入每一个作业的作业名、到达时间、服务时间、优先级（一行一个,中间用空格区分，优先级为数字越高越优先）");
        for (int i = 0; i < n; i++) {
            starr[i] = new PCB(sc.next(), sc.nextInt(), sc.nextInt(), sc.nextInt());
        }
        return starr;
    }
}
/*
A 0 3 3
B 1 6 5
C 2 1 1
D 3 4 4
E 4 2 2
 */