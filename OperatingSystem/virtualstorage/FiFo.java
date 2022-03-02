package com.process.virtualstorage;

import java.util.ArrayList;
import java.util.Iterator;

/**
 * @author: SKPrimin
 * @date: 2021/12/16  20:14
 * @ClassName: FiFo
 * @Description: TODO
 */
public class FiFo {
    /**
     * 设置分配的物理块数目pageNum
     * 页面号引用串 pageQueue
     */
    int pageNum;
    ArrayList<Integer> pageQueue;

    /**
     * 类唯一的构造器，只允许创建时直接确定好物理块数目以及页面号引用串
     */
    public FiFo(int pageNum, ArrayList<Integer> pageQueue) {
        this.pageNum = pageNum;
        this.pageQueue = pageQueue;
    }

    public void run() {
        // 定义物理块,初始化缺页次数
        ArrayList<Object> physicalBlock = new ArrayList<>(pageNum);
        int missingNum = 0;
        int time = 0;
        //时间记录表，记录物理块中各元素进入时间 直接定义为整数型
        ArrayList<Integer> enterTime = new ArrayList<>(pageNum);
        for (Object page : pageQueue) {
            // 查看本页是否在物理块中
            if (!physicalBlock.contains(page)) {
                // 缺页则再根据物理块情况判断
                missingNum++;
                // 物理块充足时无需替换，直接加入物理块中
                if (physicalBlock.size() < pageNum) {
                    physicalBlock.add(page);
                    enterTime.add(time);
                    System.out.println("缺页" + page + "，无需置换，当前物理块" + physicalBlock);
                    // 物理块不足时调用函数找出未来最远使用的一个
                } else {
                    int earindex = findEarliest(enterTime);
                    Object earliest = physicalBlock.get(earindex);
                    // 在物理块中替换
                    physicalBlock.set(earindex, page);
                    enterTime.set(earindex, time);
                    System.out.println("缺页" + page + "，置换" + earliest + "元素，当前物理块" + physicalBlock);
                }
                // 不缺页
            } else {
                System.out.println("不缺页，" + page + "在物理块" + physicalBlock + "中");
            }
            time++;
        }
        System.out.println("缺页率为" + missingNum + "/" + pageQueue.size() + " = " + missingNum * 100 / pageQueue.size() + "%");
    }

    // 找出物理块中最早进入的页面在物理块的索引
    public int findEarliest(ArrayList<Integer> tlist) {
        // 先默认第一个元素是最先进入的
        int earliest = tlist.get(0);
        int earindex = 0;
        // 遍历整个物理块
        for (int i = 0; i < tlist.size(); i++) {
            // 如果这个元素比之前一个更早进入，即对应数值更小，就替换
            if (earliest > tlist.get(i)) {
                earindex = i;
                earliest = tlist.get(i);
            }
        }
        return earindex;
    }
}

class TestFF {
    public static void main(String[] args) {
// 设置分配的物理块数目
        int pageNum = 4;
        // 初始化页面号引用串
        ArrayList<Integer> pageQueue =  new ArrayList<>();
        int[] array = {4, 3, 2, 1, 4, 3, 5, 4, 3, 2, 1, 5};
        for (int i : array) {
            pageQueue.add(i);
        }
        FiFo ff = new FiFo(pageNum, pageQueue);
        ff.run();
    }
}