package com.des.demo;

/**
 * @author: SKPrimin
 * @date 2021/12/8
 * @ClassName: GJ  12:26
 * @Description: TODO
 */

public class GJ {
    public static void main(String[] args) {

        String s1 = "011100000111001001101001011011010110100101";
        String s2 = "111100101000101110100011111001011010000010";
        // 二进制字符串转为数字 截取出钱30 后2或者18自行判断
        int len = s2.length();
        int sn1l = Integer.parseInt(s1.substring(0, 30), 2);
        int sn1r = Integer.parseInt(s1.substring(30), 2);
        int sn2l = Integer.parseInt(s2.substring(0, 30), 2);
        int sn2r = Integer.parseInt(s2.substring(30), 2);
        // 异或运算
        int snl = sn1l ^ sn2l;
        int snr = sn1r ^ sn2r;

        String left = String.format("%30s", Integer.toBinaryString(snl)).replace(' ', '0');
        String rlenfm = "%" + (len - 30) + "s";
        String right = String.format(rlenfm, Integer.toBinaryString(snr)).replace(' ', '0');

        // 生成format字符串格式参数
        System.out.println(left + right);

    }
}
