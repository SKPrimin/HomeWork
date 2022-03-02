package com.process.fcfs;

import java.util.Scanner;

/**
 * @author: SKPrimin E01914168张丞
 * @date: 2021/10/28  21:13
 * @ClassName: Test
 * @Description: TODO 测试类 用于读取输入并调用两大算法
 */
public class Test {
    public static void main(String[] args) {
        // 读取输入的数组并浅拷贝
        PCB[] arr1 = dataReadIn();
        PCB[] arr2 = new PCB[arr1.length];
        System.arraycopy(arr1, 0, arr2, 0, arr1.length);

        //调用两大算法
        FcomeFsever fcfs = new FcomeFsever();
        fcfs.dispatch(arr1);
        ShortestJobFirst sjf = new ShortestJobFirst();
        sjf.dispatch(arr2);
    }

    public static PCB[] dataReadIn() { //数据读入函数,直接设为静态函数，强制要求写入数据
        System.out.print("请输入本次需要调度的作业数目：");
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();
        PCB[] starr = new PCB[n];
        System.out.println("请输入每一个作业的作业名、到达时间、服务时间（一行一个,中间用空格区分）");
        for (int i = 0; i < n; i++) {
            starr[i] = new PCB(sc.next(), sc.nextInt(), sc.nextInt());
        }
        return starr;
    }
}
/*
A 0 4
B 1 3
C 2 5
D 3 2
E 4 4
 */