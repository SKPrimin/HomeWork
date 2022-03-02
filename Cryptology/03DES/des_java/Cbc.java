package com.des.demo;

/**
 * @author: SKPrimin
 * @date: 2021/11/22  20:41
 * @ClassName: Cbc
 * @Description: TODO
 */
public class Cbc extends DES {
    public static String encryption(String binStr, String binKey, String strIV) {
        // 生成子密钥串
        String[] binKeys48 = creatSubKeys(binKey);
        int group = binStr.length() / 64;
        // 将IV 编码成二进制
        Ecode si = new Ecode(strIV);
        si.s2n();
        String binIV = si.getBinString();
//        System.out.println("binIV" + binIV);

        StringBuilder cipher = new StringBuilder();
        // 进行第一轮的加密
        String binCbc1 = xor(binStr.substring(0, 64), binIV);
        String binCbcBefore = encryption(binCbc1, binKeys48);
        cipher.append(binCbcBefore);
        // 进行其余组的加密
        for (int i = 1; i < group; i++) {
            // 取余第i+1组
            String binCbcStri = binStr.substring(i * 64, i * 64 + 64);
            String binCbci = xor(binCbcStri, binCbcBefore);
            binCbcBefore = encryption(binCbci, binKeys48);
            cipher.append(binCbcBefore);
        }

        return cipher.toString();
    }

    public static String decryption(String binStr, String binKey, String strIV) {
        // 生成子密钥串
        String[] binKeys48 = creatSubKeys(binKey);
        int group = binStr.length() / 64;
        // 将IV 编码成二进制
        Ecode si = new Ecode(strIV);
        si.s2n();
        String binIV = si.getBinString();

        StringBuilder plaint = new StringBuilder();
        // 进行第一轮的加密
        String binCbcBefore = decryption(binStr.substring(0, 64), binKeys48);
        String binCbc1 = xor(binCbcBefore, binIV);
        plaint.append(binCbc1);
        // 进行其余组的加密
        for (int i = 1; i < group; i++) {
            // 取余第i+1组
            String binCbcStri = binStr.substring(i * 64, i * 64 + 64);

            binCbcBefore = decryption(binCbcStri, binKeys48);
            String binCbci = xor(binCbcBefore, binStr.substring(i * 64 - 64, i * 64));
            plaint.append(binCbci);
        }
        return plaint.toString();
    }

    // 字符形式的二进制异或运算 重写父类的方法 专为此处64位异或设计
    public static String xor(String s1, String s2) {
        // 二进制字符串转为数字 截取出钱30 后2或者18自行判断
        int len = s2.length();
        int sn1l = Integer.parseInt(s1.substring(0, 30), 2);
        int sn1c = Integer.parseInt(s1.substring(30, 60), 2);
        int sn1r = Integer.parseInt(s1.substring(60), 2);

        int sn2l = Integer.parseInt(s2.substring(0, 30), 2);
        int sn2c = Integer.parseInt(s2.substring(30, 60), 2);
        int sn2r = Integer.parseInt(s2.substring(60), 2);

        // 异或运算
        int snl = sn1l ^ sn2l;
        int snc = sn1c ^ sn2c;
        int snr = sn1r ^ sn2r;

        String left = String.format("%30s", Integer.toBinaryString(snl)).replace(' ', '0');
        String center = String.format("%30s", Integer.toBinaryString(snc)).replace(' ', '0');
        String rlenfm = "%" + (len - 60) + "s";
        String right = String.format(rlenfm, Integer.toBinaryString(snr)).replace(' ', '0');

        // 生成format字符串格式参数
        return left + center + right;
    }
}