package com.des.demo;

/**
 * @author: SKPrimin
 * @date: 2021/11/22  19:51
 * @ClassName: ECB
 * @Description: TODO DES 的ECB电码本模式 继承DES类中的所有方法
 */
public class Ecb extends DES {

    public static String encryption(String binPlain, String binKey) {
        // 生成子密钥串
        String[] binKeys48 = creatSubKeys(binKey);
        // 64个一组分组
        int group = binPlain.length() / 64;
        StringBuilder cipher = new StringBuilder();
        for (int i = 0; i < group; i++) {
//            System.out.println("开始第" + (i + 1) + "组加密");
            String binPlain64 = binPlain.substring(i * 64, (i + 1) * 64);
            cipher.append(encryption(binPlain64, binKeys48));
        }
        return cipher.toString();
    }

    public static String decryption(String binCipher, String binKey) {
        // 生成子密钥串
        String[] binKeys48 = creatSubKeys(binKey);
        // 64个一组分组
        int group = binCipher.length() / 64;
        StringBuilder plain = new StringBuilder();
        for (int i = 0; i < group; i++) {
            String binCipher64 = binCipher.substring(i * 64, (i + 1) * 64);
            plain.append(decryption(binCipher64, binKeys48));
        }
        return plain.toString();
    }
}
