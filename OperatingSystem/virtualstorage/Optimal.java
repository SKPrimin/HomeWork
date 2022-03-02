package com.process.virtualstorage;

import java.util.*;

/**
 * @author: SKPrimin
 * @date: 2021/12/16  18:20
 * @ClassName: Optimal
 * @Description: TODO
 */
public class Optimal {
    /**
     * 设置分配的物理块数目pageNum
     * 页面号引用串 pageQueue
     */
    int pageNum;
    ArrayList pageQueue;

    /**
     * 类唯一的构造器，只允许创建时直接确定好物理块数目以及页面号引用串
      */
    public Optimal(int pageNum, ArrayList pageQueue) {
        this.pageNum = pageNum;
        this.pageQueue = pageQueue;
    }

    public void run() {
        // 定义物理块,初始化缺页次数
        ArrayList physicalBlock = new ArrayList(pageNum);
        int missingNum = 0;
        int index = 0;
        Iterator itpQ = pageQueue.iterator();
        while (itpQ.hasNext()) {
            Object page = itpQ.next();
            // 查看本页是否在物理块中
            if (!physicalBlock.contains(page)) {
                // 缺页则再根据物理块情况判断
                missingNum++;
                // 物理块充足时无需替换，直接加入物理块中
                if (physicalBlock.size() < pageNum) {
                    physicalBlock.add(page);
                    System.out.println("缺页" + page + "，无需置换，当前物理块" + physicalBlock);
                    // 物理块不足时调用函数找出未来最远使用的一个
                } else {
                    List<Object> al = new ArrayList<Object>(pageQueue.subList(index+1, pageQueue.size()));
                    Object farthest = findFarthest((ArrayList) al,physicalBlock);
                    int farIndex = physicalBlock.indexOf(farthest);
                    // 在物理块中替换
                    physicalBlock.set(farIndex, page);
                    System.out.println("缺页" + page + "，置换" + farthest + "元素，当前物理块" + physicalBlock);
                }
                // 不缺页
            } else {
                System.out.println("不缺页，" + page + "在物理块" + physicalBlock + "中");
            }
            index++;
        }
        System.out.println("缺页率为" + missingNum + "/" + pageQueue.size() + " = " + missingNum* 100 / pageQueue.size()  + "%");
    }

    // 找出物理块中最远使用的页面在物理块的索引以及页面号
    public Object findFarthest(ArrayList alist, ArrayList pblist) {

        // 如果这个元素在后续列表中不存在，那么这是永远都用不到的，直接返回
        for (Object item : pblist) {
            if (!alist.contains(item))
                return item;
        }
        // 先默认要替换第一个页
        Object farthest = pblist.get(0);
        // index如果找不到会报错，故先行处理找不到的情况
        int last = alist.indexOf(pblist.get(0));
        // 遍历整个物理块
        for (Object item : pblist) {
            int now = alist.indexOf(item);
            // 如果这个元素比之前一个离得更远，就替换
            if (last < now) {
                last = now;
                farthest = item;
            }
        }
        return farthest;
    }
}


class TestO{
    public static void main(String[] args) {
        // 设置分配的物理块数目
        int pageNum = 3;
        // 初始化页面号引用串
        ArrayList pageQueue = new ArrayList();
        int[] array = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
        for (int i :array){
            pageQueue.add(i);
        }
        Optimal op = new Optimal(pageNum, pageQueue);
        op.run();
    }
}