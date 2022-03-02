package com.process.banker;

import java.util.Arrays;

/**
 * @author: SKPrimin E01914168 张丞
 * @date: 2021/11/25  20:14
 * @ClassName: Proces
 * @Description: TODO 用于银行家算法中的进程定义
 */
public class Proces {

    String pName;
    int[] pMax;
    int[] pAllocation;
    int[] pNeed;
    private boolean finish;
    int[] pRequest;

    public Proces(String pName, int[] pMax, int[] pAllocation, int[] pNeed) {
        // 由于本次数据输入较多，容易出错，使用异常处理保证不会前功尽弃
        if (pMax.length != pAllocation.length && pMax.length != pNeed.length) {
            throw new IllegalArgumentException("输入数据有误，三个数组必须长度一致");
        }
        if (!Arrays.equals(pNeed, BlankerAlgorithm.sub(pMax, pAllocation))) {
            throw new IllegalArgumentException("输入数据有误，" + pName + "未满足Need" + Arrays.toString(pNeed) +
                    " = (Max - Allocation)" + Arrays.toString(BlankerAlgorithm.sub(pMax, pAllocation)));
        }
        this.pName = pName;
        this.pMax = pMax;
        this.pAllocation = pAllocation;
        this.pNeed = pNeed;
        this.pRequest = pNeed;
        this.finish = false;
    }

    public boolean isFinish() {
        return finish;
    }

    public void setFinish(boolean finish) {
        this.finish = finish;
    }


    @Override
    public String toString() {
        return "Proces{" +
                "pName='" + pName + '\'' +
                ", pNeed=" + Arrays.toString(pNeed) +
                ", pAllocation=" + Arrays.toString(pAllocation) +
                ", pMax=" + Arrays.toString(pMax) +
                ", finish=" + finish +
                ", pRequest=" + Arrays.toString(pRequest) +
                '}';
    }
}
