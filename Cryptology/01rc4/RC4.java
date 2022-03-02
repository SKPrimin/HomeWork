package com.origin.rc4;

import java.util.Arrays;

/**
 * @author: SKPrimin
 * @date: 2021/10/17  13:26
 * @ClassName: RC4
 * @Description: TODO
 */
public class RC4 {
    public RC4() {
    }

    public int[] Dataoriginal;
    public int[] Keyoriginal;

    public RC4(int[] dataoriginal, int[] keyoriginal) {
        Dataoriginal = dataoriginal;
        Keyoriginal = keyoriginal;
    }

    public void mainRC4() {
        // 初始化S表
        int[] tableS = setTableSK(Keyoriginal, Keyoriginal.length);
        // 生成密钥流
        int length = Dataoriginal.length;
        int[] KeyStream = new int[length];
        KeyStream = getKeyStream(tableS, KeyStream, length);

        // 明文与密钥流异或运算加密
        int[] Datacryption = getRC4(KeyStream, Dataoriginal, length);
        System.out.println(("加密结果为：" + Arrays.toString(Datacryption)));
        // 密文与密钥流异或运算解密
        int[] Dataendecryption = getRC4(KeyStream, Datacryption, length);
        System.out.println("解密结果为：" + Arrays.toString(Dataendecryption));
    }

    public int[] setTableSK(int[] tableKoriginal, int length) {
        // 初始化线性表 S
        int[] tableS = new int[256];
        int[] tableK = new int[258];
        // 初始化S,K 表，即线性填充
        for (int i = 0; i < 256; i++) {
            Arrays.fill(tableS, i);
        }
        for (int i = 0; i < 256 / length + 1; i++) {
            System.arraycopy(tableKoriginal, 0, tableK, i * length, length);
        }
        tableK = Arrays.copyOf(tableK, 256);

        // 已经获得原始的 S，K表。现在⽤K表对S表进⾏初始置换
        int j = 0;
        for (int i = 0; i < 256; i++) {
            j = (j + tableS[i] + tableK[i]) % 256;
            // 无需借助中间变量，即可完成两值交换
            tableS[i] = tableS[i] + tableS[j];
            tableS[j] = tableS[i] - tableS[j];
            tableS[i] = tableS[i] - tableS[j];
        }
        return tableS;
    }

    public int[] getKeyStream(int[] tableS, int[] KeyStream, int length) {
        //生成密钥流（为每个待加密的字节⽣成⼀个伪随机数）
        int i = 0;
        int j = 0;
        int t = 0;
        for (int r = 0; r < length; r++) {
            i = (i + 1) % 256;
            j = (j + tableS[i]) % 256;
            tableS[i] = tableS[i] + tableS[j];
            tableS[j] = tableS[i] - tableS[j];
            tableS[i] = tableS[i] - tableS[j];
            t = (tableS[i] + tableS[j]) % 256;
            KeyStream[r] = tableS[t];
        }
        return KeyStream;
    }

    public int[] getRC4(int[] Key, int[] Text, int length) {
        //RC4异或过程
        for (int i = 0; i < length; i++) {
            Text[i] = Key[i] ^ Text[i];
        }
        return Text;
    }
}

