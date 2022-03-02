package com.des.demo;

import java.util.Scanner;

/**
 * @Author: SKPrimin
 * @Date 2021/12/9 0:02
 * @ClassName: Test
 * @Description: TODO
 */

public class Test {
    public static void main(String[] args) {

/*
        // 直接定义明文密钥
        String str = "11112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222111122221111222211112222";
        String key = "12345678";
        System.out.println("将要加密的内容为" + str);
        System.out.println("密钥为" + key);
*/

        // 控制台输入内容
        Scanner sc = new Scanner(System.in);
        System.out.println("请输入想要加密的内容");
        String str = sc.nextLine();


        System.out.println("请输入密钥");
        String key = sc.nextLine();


        // 进行字符编码
        Ecode gin = new Ecode(str);
        gin.s2n();
        String plaint = gin.getBinString();


        // ECB  模式
        System.out.println("\n欢迎来到ECB模式");
        String ciphere = Ecb.encryption(plaint, key);
        System.out.println("密文为" + ciphere);

       /* //截取替换
        String replace = String.format("%64s", "0").replace(' ', '0');
        ciphere = ciphere.substring(0, 64) + replace + ciphere.substring(128);
        System.out.println("修改后的密文为" + ciphere);*/

        String plaintoute = Ecb.decryption(ciphere, key);
        System.out.println("明文为" + plaintoute);

        Ecode goute = new Ecode(plaintoute);
        goute.n2s();
        String plaintoutchare = goute.getStringChar();
        System.out.println("ECB解密" + plaintoutchare);

        // CBC  模式
        System.out.println("\n欢迎来到CBC模式");
/*        String iv = "11112222";
        System.out.println("iv为" + iv);*/
        System.out.println("请输入IV");
        String iv = sc.nextLine();

        String cipherc = Cbc.encryption(plaint, key, iv);
        System.out.println("加密得到的密文为" + cipherc);

//        //截取替换
//        cipherc = cipherc.substring(0, 64) + replace + cipherc.substring(128);
//        System.out.println("修改后的密文为" + cipherc);

        String plaintoutc = Cbc.decryption(cipherc, key, iv);
        System.out.println("解密得到的明文为" + plaintoutc);

        Ecode goutc = new Ecode(plaintoutc);
        goutc.n2s();
        String plaintoutcharc = goutc.getStringChar();
        System.out.println("CBC解密" + plaintoutcharc);
    }
}
