package com.des.demo;

import java.io.*;

/**
 * @Author: SKPrimin
 * @Date 2021/12/6 18:31
 * @ClassName: FileRW
 * @Description: TODO
 */

public class FileRW {
    public static void main(String[] args) {
        //1.1有一个源文件
        File f1 = new File("Cryptology/src/com/des/demo/testin.txt");
        //1.2有一个目标文件：
        File f2 = new File("Cryptology/src/com/des/demo/output.txt");
        //2.1搞输入的管和输出的管，并分别接到源文件和目标文件上
        try (
                FileReader fr = new FileReader(f1);
                FileWriter fw = new FileWriter(f2);
        ) {
            //3利用缓冲字符数组，将数组转为String写出
            char[] ch = new char[8];
            int len = fr.read(ch);
            while (len != -1) {
                String str = new String(ch, 0, len);
                String key = "12345678";
                System.out.println("将要加密的内容为" + str);
                System.out.println("密钥为" + key);

                // 进行字符编码
                Ecode gin = new Ecode(str);
                gin.s2n();
                String plaint = gin.getBinString();

                // ECB  模式
                System.out.println("\n欢迎来到ECB模式");
                String ciphere = Ecb.encryption(plaint, key);
                System.out.println("密文为" + ciphere);

                String plaintoute = Ecb.decryption(ciphere, key);
                System.out.println("明文为" + plaintoute);

                Ecode goute = new Ecode(plaintoute);
                goute.n2s();
                String plaintoutchare = goute.getStringChar();
                System.out.println("\nECB解密" + plaintoutchare);
                // 写入文件
                fw.write("\nECB模式\n 密文：" + ciphere + "\n明文：" + plaintoute + "\n解码：" + plaintoutchare);

                // CBC  模式
                System.out.println("\n欢迎来到CBC模式");
                String iv = "11112222";
                System.out.println("iv为" + iv);

                String cipherc = Cbc.encryption(plaint, key, iv);
                System.out.println("加密得到的密文为" + cipherc);

                String plaintoutc = Cbc.decryption(cipherc, key, iv);
                System.out.println("解密得到的明文为" + plaintoutc);

                Ecode goutc = new Ecode(plaintoutc);
                goutc.n2s();
                String plaintoutcharc = goutc.getStringChar();
                System.out.println("CBC解密" + plaintoutcharc);
                // 写入文件
                fw.write("\nCBC模式\n 密文：" + cipherc + "\n明文：" + plaintoutc + "\n解码" + plaintoutcharc);
                len = fr.read(ch);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
