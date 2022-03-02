package com.process.diskscan;

import java.util.ArrayList;

/**
 * @Author: SKPrimin
 * @Date 2021/12/18 16:12
 * @ClassName: ScanDisk
 * @Description: TODO 扫描算法与循环扫描的公共类 定义变量结构和分组方法
 */

public class ScanDisk {
    /**
     * diskCollection ArrayList类型数据，为初始的磁道号序列
     */
    protected ArrayList<Integer> diskCollection;
    /**
     * start int类型数据，为磁道开始，默认向磁道号增加的方向访问
     */
    protected int start;
    /**
     * timeList ArrayList类型数据，为访问磁道对应的移动距离
     */
    protected ArrayList<Integer> movList = new ArrayList<>();
    /**
     * distanceSum int类型数据，磁针寻道总道数
     */
    protected int distanceSum;
    /**
     * diskList ArrayList类型数据，为排序好的磁道访问顺序
     */
    protected ArrayList<Integer> diskList = new ArrayList<>();
    /**
     * diskListBefore ArrayList类型数据，为磁针优先访问的磁道序列 由里向外访问顺序
     */
    protected ArrayList<Integer> diskListBefore = new ArrayList<>();
    /**
     * diskListAfter ArrayList类型数据，为磁针后访问的磁道序列 由外向里访问顺序
     */
    protected ArrayList<Integer> diskListAfter = new ArrayList<>();

    /**
     * separate分割方法，以起始点为分界线，将磁道分为前后连个顺序
     */
    protected void separate() {
        // 遍历 diskCollection
        for (int item : diskCollection) {
            // 若在起始点外边在第一轮访问
            if (item > start) {
                diskListBefore.add(item);
                // 在起始点里边则在后一轮访问
            } else {
                diskListAfter.add(item);
            }
        }
    }

    /**
     * 计算距离函数通过三元运算符返回两数绝对值
     *
     * @param a 一个位置
     * @param b 另一个点位置
     * @return 两个位置之间的距离
     */
    protected int distance(int a, int b) {
        return a > b ? a - b : b - a;
    }


    /**
     * 排序函数
     *
     * @param arrayList 要排序的数组列表
     * @param reverse   是否逆序 false为升序，true为逆序
     * @return 返回已经排序好的数组列表
     */
    public ArrayList<Integer> sort(ArrayList<Integer> arrayList, boolean reverse) {
        int len = arrayList.size();
        for (int i = 0; i < len; i++) {
            int index = i;
            for (int j = i + 1; j < len; j++) {
                // 若 reverse为false 升序排序 reverse为true则降序排序
                if (!reverse) {
                    if (arrayList.get(j) < arrayList.get(index)) {
                        index = j;
                    }
                } else {
                    if (arrayList.get(j) > arrayList.get(index)) {
                        index = j;
                    }
                }
            }
            //位置交换 将较小reverse=false  /较大reverse=true 的数提到前边
            int temp = arrayList.get(index);
            arrayList.set(index, arrayList.get(i));
            arrayList.set(i, temp);
        }
        return arrayList;
    }

    public void calculateTravelDistance() {
        // 定义磁盘针头
        int pinhead = start;
        // 计算访问磁道号时的移动距离
        for (int i = 0; i < diskList.size(); i++) {
            // 将对应位置设置为距离 并统计总数
            movList.add(distance(pinhead, diskList.get(i)));
            distanceSum += movList.get(i);
            pinhead = diskList.get(i);
        }
    }
}
