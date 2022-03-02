package com.des.demo;

/**
 * @author: SKPrimin
 * @date 2021/12/7
 * @ClassName: Ecode  12:49
 * @Description: TODO 因为二进制过长，java中只能使用字符串
 */

public class Ecode {
    public String str;
    public int len;
    private char[] array;
    private String[] binarray;
    private StringBuilder sb = new StringBuilder();
    private StringBuilder stringChar = new StringBuilder();

    // 规定所有组创建时必须有字符
    public Ecode(String str) {
        this.str = str;
    }

    // 编码时得到可变二进制字符串
    public StringBuilder getSb() {
        return sb;
    }

    // 编码时得到二进制字符串
    public String getBinString() {
        return sb.toString();
    }

    // 解码时得到字符串
    public String getStringChar() {
        return stringChar.toString();
    }

    // String to Number 编码
    public void s2n() {
        this.array = str.toCharArray();
        this.len = str.length();
        this.binarray = new String[len];
        for (int i = 0; i < len; i++) {
            // 逐个读取出字符
            char ch = array[i];
            // 转为二进制形式，以字符串存储
            // 如下是将字符定为8位，不足补零的两种方式，调用format或者做if els
            String binch = String.format("%8s", Integer.toBinaryString(ch)).replace(' ', '0');

/*            String binch = Integer.toBinaryString(ch);
            int binlen = binch.length();
            if (binlen == 6) {
                binch = "00" + binch;
            } else if (binlen == 7 || binlen == 15) {
                binch = "0" + binch;
            } else if (binlen != 8) {
                System.out.println("该字符符有问题");
            }*/
            binarray[i] = binch;
            sb.append(binch);
        }
        int lack = sb.length()%64;
        if (lack!=0){
            String parameters = "%"+(64-lack)+"s";
            String lastone = String.format(parameters, "0").replace(' ', '0');
            sb.append(lastone);
        }




    }

    // Number to String 解码 将二进制字符转为字符
    public void n2s() {
        // 获得字符长度 并分组
        this.len = str.length();
        for (int i = 0; i < len / 8; i++) {
            String item = str.substring(i * 8, i * 8 + 8);
            int ass = Integer.parseInt(item, 2);
            stringChar.append((char) ass);
        }
    }
}