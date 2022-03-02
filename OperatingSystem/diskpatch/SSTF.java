package com.process.diskpatch;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * @Author: SKPrimin
 * @Date 2021/12/17 0:22
 * @ClassName: SSTF
 * @Description: TODO
 */

public class SSTF extends DiskDispatch {
    /**
     * trackSequence为SSTF调度的磁道号数组
     * len 为传出的磁道号数目
     */
    private int[] trackSequence;
    private int len;


    // 构造器
    public SSTF(int start, ArrayList<Integer> track) {
        this.start = start;
        this.track = track;
        this.len = track.size();
        movdistan = new int[len];
        trackSequence = new int[len];
    }

    /**
     */
    public void run() {
        // 初始化磁针位置     * 调度执行函数，进行此次最短寻道时间优先磁盘调度
        int needle = start;
        for (int i = 0; i < len; i++) {
            // 求出移动距离的磁道号以及移动距离
            Track tc = shortest(needle, track);
            // 将算出的将要访问的下一磁道号、移动距离加入对应数组
            trackSequence[i] = tc.diskName;
            movdistan[i] = tc.distance;
            distanceSum += movdistan[i];
            // 更新指针位置以及磁道号列表，去除已经访问的磁道号
            needle = tc.diskName;
            // 此处使用包装类包装，避免当成索引
            track.remove(Integer.valueOf(tc.diskName));
        }
    }

    /**
     * 在给定范围内找出里磁针最近的磁道号
     *
     * @param needle 磁针当前位置
     * @param array  访问磁道号数组,即查找范围
     * @return 查找到的要访问的磁道号
     */
    public Track shortest(int needle, ArrayList<Integer> array) {
        // 各变量初始化 先默认第一个是距离最近的磁道
        Track tc = new Track();
        tc.diskName = array.get(0);
        tc.distance = distance(needle, array.get(0));
        // 进过遍历，若发现有离得更近的就替换
        for (int item :
                array) {
            if (distance(needle, item) < tc.distance) {
                tc.diskName = item;
                tc.distance = distance(needle, item);
            }
        }
        return tc;
    }

    @Override
    public String toString() {
        return "\n最短寻道时间优先SSTF" +
                "\n从" + start + "号磁道开始" +
                "\n被访问的下一个磁道号\t" + Arrays.toString(trackSequence) +
                "\n移动距离（磁道数）\t" + Arrays.toString(movdistan) +
                "\n总道数："+distanceSum+"\t平均寻道长度：" + String.format("%.2f", (double) distanceSum / len);
    }
}
