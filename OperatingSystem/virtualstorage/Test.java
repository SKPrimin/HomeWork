package com.process.virtualstorage;

import java.util.ArrayList;

/**
 * @author: SKPrimin
 * @date: 2021/12/16  20:42
 * @ClassName: Test
 * @Description: TODO
 */
public class Test {
    public static void main(String[] args) {
        // 设置分配的物理块数目
        int pageNum = 3;
        // 初始化页面号引用串
        ArrayList<Integer> pageQueue = new ArrayList<>();
        int[] array = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
        for (int i :array){
            pageQueue.add(i);
        }


        System.out.println("最佳(Optimal)置换算法");
        Optimal op = new Optimal(pageNum, pageQueue);
        op.run();

        System.out.println("\n先进先出(FIFO)页面置换算法");
        FiFo ff = new FiFo(pageNum, pageQueue);
        ff.run();

        System.out.println("\nLRU(Least Recently Used)置换算法");
        LRU lr = new LRU(pageNum, pageQueue);
        lr.run();
    }

}
