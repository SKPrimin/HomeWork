package com.process.diskpatch;

import java.util.ArrayList;

/**
 * @Author: SKPrimin
 * @Date 2021/12/17 0:20
 * @ClassName: Test
 * @Description: TODO 测试类 集中测试磁盘调度算法
 */

public class Test {
    public static void main(String[] args) {
        // 磁盘号顺序
        int[] track = new int[]{98, 183, 37, 122, 14, 124, 65, 67};
        ArrayList<Integer> ta = new ArrayList<>();
        for (int t : track) {
            ta.add(t);
        }

        // 先来先服务
        FCFS ff = new FCFS(53, ta);
        ff.run();
        System.out.println(ff);

        //最短寻道时间优先
        SSTF st = new SSTF(53, ta);
        st.run();
        System.out.println(st);

    }
}