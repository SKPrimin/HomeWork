package com.process.banker;

/**
 * @author: SKPrimin  E01914168 张丞
 * @date: 2021/11/25  19:29
 * @ClassName: Test
 * @Description: TODO 测试类 调用银行家算法
 */
public class Test {
    public static void main(String[] args) {

        Proces[] pArr = new Proces[5];
        pArr[0] = new Proces("P0", new int[]{7, 5, 3}, new int[]{0, 1, 0}, new int[]{7, 4, 3});
        pArr[1] = new Proces("P1", new int[]{3, 2, 2}, new int[]{2, 0, 0}, new int[]{1, 2, 2});
        pArr[2] = new Proces("P2", new int[]{9, 0, 2}, new int[]{3, 0, 2}, new int[]{6, 0, 0});
        pArr[3] = new Proces("P3", new int[]{2, 2, 2}, new int[]{2, 1, 1}, new int[]{0, 1, 1});
        pArr[4] = new Proces("P4", new int[]{4, 3, 3}, new int[]{0, 0, 2}, new int[]{4, 3, 1});

        BlankerAlgorithm ba = new BlankerAlgorithm(new int[]{3, 3,2});
        ba.dispatch(pArr);
    }
}
