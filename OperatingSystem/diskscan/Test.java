package com.process.diskscan;

import java.util.ArrayList;

/**
 * @Author: SKPrimin
 * @Date 2021/12/18 17:27
 * @ClassName: Test
 * @Description: TODO 基于扫描的磁盘调度算法
 */

public class Test {
    public static void main(String[] args) {
        // 磁盘号顺序
        int[] track = new int[]{55, 58, 39, 18, 90, 160, 150, 38,184};
        ArrayList<Integer> ta = new ArrayList<>();
        for (int t : track) {
            ta.add(t);
        }

        // 先来先服务
        SCAN ff = new SCAN( ta,100);
        ff.run();
        System.out.println(ff);

        //最短寻道时间优先
        CSCAN st = new CSCAN( ta,100);
        st.run();
        System.out.println(st);

    }
}
