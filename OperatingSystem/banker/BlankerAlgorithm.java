package com.process.banker;

import java.util.ArrayList;
import java.util.Arrays;

/**
 * @author: SKPrimin E01914168 张丞
 * @date: 2021/11/25  19:13
 * @ClassName: BlankerAlgorithm
 * @Description: TODO 银行家算法，避免死锁 调度算法及其所使用的数组加减法，进程状态检测，试探调度后的安全性检测
 */
public class BlankerAlgorithm {

    /**
     * 可用资源向量
     * 创建一个银行家算法时必须有可用资源，禁止创建空实例
     */
    int[] available;

    public BlankerAlgorithm(int[] available) {
        this.available = available;
    }

    public void dispatch(Proces[] pArr) {
        // 先判断可用资源向量与进程的各向量长度是否一致
        if (available.length != pArr[0].pAllocation.length) {
            throw new IllegalArgumentException("进程资源种类不适配");
        }

        ArrayList<String> securitySequence = new ArrayList<String>();

        for (int i = 0; i < pArr.length; i++) {
            // 遍历整个队列
            for (Proces p : pArr) {
                // 先进行检查，通过后会试探性的分配资源
                if (check(p)) {
                    // 打印当前进程调度信息
                    System.out.print(p.pName+ "检查通过" );
                    System.out.println("\t当前可用资源"+Arrays.toString(available));
                    System.out.println(p);

                    /*系统将资源调度给这个进程 从available分配给其 请求的资源
                    * 当前已分配的资源等于原分配的加上刚刚申请的
                    * 所需要的的资源减去已经申请到的
                    * */
                    available = sub(available, p.pRequest);
                    p.pAllocation = add(p.pAllocation, p.pRequest);
                    p.pNeed = sub(p.pNeed, p.pRequest);
                    // 该进程试探性调度完成，释放占有的所有资源
                    available = add(available, p.pAllocation);

                    // 如果通过安全性检查将正式分配资源，并将此进程设为完成态，添加到安全性队列中
                    if (securityAlgorithm(pArr, available)) {
                        System.out.println("试探分配"+p.pName+"，通过安全性检查\n");
                        p.setFinish(true);
                        securitySequence.add(p.pName);
                    } else {
                        // 未通过安全性检查则试探分配作废，原样回退数据，进行下一个进程试调度
                        System.out.println("试探分配"+p.pName+"，未通过安全性检查\n");
                        available = add(available, p.pRequest);
                        p.pAllocation = sub(p.pAllocation, p.pRequest);
                        p.pNeed = add(p.pNeed, p.pRequest);
                    }
                    break;
                }
            }
        }
        System.out.println("安全序列：{"+securitySequence+"}");
    }

    // 检查判断，检查p发出请求资源后Request <= Need 和 Request <= Available
    public boolean check(Proces p) {
        // 本进程未完成再继续检查
        if (!p.isFinish()) {
            // 如果 Request <= Need便继续检查，否则认为出错
            if (nonNegative(sub(p.pNeed, p.pRequest))) {
                // 如果Request <= Available ，即调度可行性检查通过，返回 true
                return nonNegative(sub(available, p.pRequest));
            }
            return false;
        }
        return false;
    }

    // 安全性算法
    public boolean securityAlgorithm(Proces[] pArr, int[] available) {
        // 首先设置两个向量：工作向量work、Finish
        // 工作向量work,表示系统可以提供给进程继续运行所需的各类资源数目，执行安全性算法开始时，work=available
        int[] work = available;
        /* Finish,表示系统是否有足够的资源分配给进程，使之运行完成，开始时Finish[i]=false;
         * 布尔数组默认初始化恰好是false.当有足够资源分配给进程时，再令Finish[i] = true*/
        boolean[] finish = new boolean[pArr.length];

        //对所有进程进行一轮进行安全性检查，确保即使在最差的情况下也能遍历完全
        for (int j = 0; j < pArr.length; j++) {
            //在未试探的进程中先找到一个Need[i,j]<=work的进程，找到则进行分配，未找到做外出判断
            for (int i = 0; i < pArr.length; i++) {
                if (!finish[i] && nonNegative(sub(work, pArr[i].pNeed))) {
                    // 将释放的资源加入进work；本进行检查完成设为ture；退出本轮次循环，寻找下一个
                    work = add(work, pArr[i].pAllocation);
                    finish[i] = true;
                }
            }
        }
        // 如果有一个false,即不存在安全序列，返回false,全部通过检测才会返回true
        for (boolean i : finish) {
            if (!i) {
                return false;
            }
        }
        return true;
    }

    // 提供静态方法数组加法
    public static int[] sub(int[] a, int[] b) {
        int num = a.length;
        int[] c = new int[num];
        for (int i = 0; i < num; i++) {
            c[i] = a[i] - b[i];
        }
        return c;
    }

    // 加法静态方法数组减法
    public static int[] add(int[] a, int[] b) {
        int num = a.length;
        int[] c = new int[num];
        for (int i = 0; i < num; i++) {
            c[i] = a[i] + b[i];
        }
        return c;
    }

    // 检测本向量是否非负，即用于检测两个矩阵相减结果是否符合，避免非法
    public static boolean nonNegative(int[] array) {
        for (int i : array) {
            if (i < 0) {
                return false;
            }
        }
        return true;
    }
}