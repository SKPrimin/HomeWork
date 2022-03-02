package com.process.rr;

import java.util.Scanner;

/**
 * @author: SKPrimin E01914168张丞
 * @date: 2021/11/11  21:13
 * @ClassName: Test
 * @Description: TODO 测试类 用于读取输入并调用两大算法
 */
public class Test {
    public static void main(String[] args) {
        // 设置时间片长度
        System.out.print("时间片轮转算法\n请设置时间片长度q = ");
        Scanner sc = new Scanner(System.in);
        int timeSlice = sc.nextInt();
        // 读取输入的数组
        PCB[] arr1 = dataReadIn();
        //调用时间片轮转算法
        RR rr = new RR();
        rr.dispatch(arr1, timeSlice);

    }

    public static PCB[] dataReadIn() { //数据读入函数,直接设为静态函数，强制要求写入数据
/*        System.out.print("请输入本次需要调度的作业数目：");
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        PCB[] starr = new PCB[n];
        System.out.println("请输入每一个作业的作业名、到达时间、服务时间（一行一个,中间用空格区分）");
        for (int i = 0; i < n; i++) {
            starr[i] = new PCB(sc.next(), sc.nextInt(), sc.nextInt());
        }*/

        PCB[] starr = new PCB[5];
        starr[0] = new PCB("A", 0, 4);
        starr[1] = new PCB("B",1,3);
        starr[2] = new PCB("C",2,4);
        starr[3] = new PCB("D",3,2);
        starr[4] = new PCB("E",4,4);
        return starr;
    }
}
/*
A 0 4
B 1 3
C 2 4
D 3 2
E 4 4
 */