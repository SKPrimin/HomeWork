package com.des.demo;

/**
 * @author: SKPrimin
 * @date: 2021/12/6  21:35
 * @ClassName: DES
 * @Description: TODO DES类，继承BOX类中的所有盒子
 */
public class DES extends Box {

    //DES密钥扩展算法
    public static String[] creatSubKeys(String key) {
        // 创建编码类对象 并将密钥转为64位长的二进制字符串
        Ecode k1 = new Ecode(key);
        k1.s2n();
        StringBuilder key64 = k1.getSb();
        StringBuilder key56 = new StringBuilder();

        // 64位变56位 使用PC_1表格进行操作
        for (int i = 0; i < 56; i++) {
            key56.append(key64.charAt(PC_1[i] - 1));
        }
        // 子密钥列表 16个子密钥
        String[] subKeys = new String[16];
        //初始化 C D
        String C = key56.substring(0, 28);
        String D = key56.substring(28, 56);

        // 移位次数 16个项中12个都是2，初始化为2

        for (int i = 0; i < 16; i++) {
            int shiftStep = 2;
            if (i == 0 || i == 1 || i == 8 || i == 15) {
                //1 2 9 16 轮仅位移1
                shiftStep = 1;
            }
            // C D 左移2或1位 调用自定义的位移方法
            C = leftMove(C, shiftStep);
            D = leftMove(D, shiftStep);
            // CD 字符串合并
            String CD;
            CD = C + D;
            // 通过PC_2置换，将56位变成48位
            StringBuilder key48 = new StringBuilder();
            for (int j = 0; j < 48; j++) {
                key48.append(CD.charAt(PC_2[j] - 1));
            }
            subKeys[i] = key48.toString();
        }
        return subKeys;
    }

    //自定义字符串左移n位方法
    private static String leftMove(String str, int position) {
        String str1 = str.substring(position);
        String str2 = str.substring(0, position);
        return str1 + str2;
    }

    // 初始 IP 置换
    public static String iPReplace(String binStr64) {
        StringBuilder ipStr = new StringBuilder();
        for (int i = 0; i < 64; i++) {
            ipStr.append(binStr64.charAt(IP[i] - 1));
        }
        return ipStr.toString();
    }

    // 逆初始 FP 置换
    public static String fPReplace(String binStr64) {
        StringBuilder fpStr = new StringBuilder();
        for (int i = 0; i < 64; i++) {
            fpStr.append(binStr64.charAt(FP[i] - 1));
        }
        return fpStr.toString();
    }

    // 拓展置换E 32 -> 48
    public static String replE(String binStr32) {
        StringBuilder eStr48 = new StringBuilder();
        for (int i = 0; i < 48; i++) {
            eStr48.append(binStr32.charAt(E[i] - 1));
        }
        return eStr48.toString();
    }

    // S盒代换 48 -> 32
    public static String replS(String binStr48) {
        int si = 0;
        StringBuilder binStr32 = new StringBuilder();
        // 48 个字符每组6个，共8组，
        for (int i = 0; i < 8; i++) {
            // 截取出6长度的一组 隔6个截取一次
            String binStr6 = binStr48.substring(i * 6, i * 6 + 6);
            // 总字符串中截取出 首尾作为行号 中间部分作为列号
            String row = String.valueOf(binStr6.charAt(0)) + binStr6.charAt(5);
            String col = binStr6.substring(1, 5);
            // 将字符作为二进制解析出数字
            int rown = Integer.parseInt(row, 2);
            int coln = Integer.parseInt(col, 2);
            // 根据S盒 4行16列的排布算出在一维状态下的索引
            int index = 16 * rown + coln;
            // 找到对应的S盒的对应位置进行代换 si++ 在执行一次后自动加一
            int bitn4 = S[i][index];
            //讲格式定为4个，不足补空位，后续替换为0
            String binStr4 = String.format("%4s", Integer.toBinaryString(bitn4)).replace(' ', '0');
            // binStr4逐个添加
            binStr32.append(binStr4);
        }
        return binStr32.toString();
    }

    // 取得S盒变换的结果后再进行一次P置换
    public static String replP(String binStr32) {
        StringBuilder sb32 = new StringBuilder();
        for (int i = 0; i < 32; i++) {
            sb32.append(binStr32.charAt(P[i] - 1));
        }
        return sb32.toString();
    }

    // 字符形式的二进制异或运算
    public static String xor(String s1, String s2) {
        // 二进制字符串转为数字 截取出钱30 后2或者18自行判断
        int len = s2.length();
        int sn1l = Integer.parseInt(s1.substring(0, 30), 2);
        int sn1r = Integer.parseInt(s1.substring(30), 2);
        int sn2l = Integer.parseInt(s2.substring(0, 30), 2);
        int sn2r = Integer.parseInt(s2.substring(30), 2);
        // 异或运算
        int snl = sn1l ^ sn2l;
        int snr = sn1r ^ sn2r;
        // 格式化字符串
        String left = String.format("%30s", Integer.toBinaryString(snl)).replace(' ', '0');
        String rlenfm = "%" + (len - 30) + "s";
        String right = String.format(rlenfm, Integer.toBinaryString(snr)).replace(' ', '0');

        // 生成format字符串格式参数
        return left + right;
    }

    public static String feistel(String binStr32, String subKey48) {
        // 扩展置换 E 32->48
        String binE48 = replE(binStr32);
        // 异或运算
        String binXor48 = xor(binE48, subKey48);
        // S盒代换 48->32
        String binS32 = replS(binXor48);
        // P 盒置换
        String binP32 = replP(binS32);
        return binP32;
    }

    // 加密过程
    public static String encryption(String binPlain64, String[] binKeys48) {
        // 初始IP置换
        String binIP = iPReplace(binPlain64);
        // 分割成左右两部分 Li Ri
        String left = binIP.substring(0, 32);
        String right = binIP.substring(32);
        // 定义 Li-1  Ri-1
        String beforeLeft;
        String beforeRight;
        // 16轮 Feistel 转换
        // Li=Ri-1    Ri=Li-1 ^ F(Ri-1, Ki)
        for (int i = 0; i < 16; i++) {
            beforeLeft = left;
            beforeRight = right;
            left = beforeRight;
            right = xor(beforeLeft, feistel(beforeRight, binKeys48[i]));
//            System.out.println("第" + (i + 1) + "轮的加密结果为" + left + right);
        }
        // 最后一轮交换后得到结果
        String encryptionText = right + left;
        return fPReplace(encryptionText);
    }

    public static String decryption(String binPlain64, String[] binKeys48) {
        // 初始IP置换
        String binIP = iPReplace(binPlain64);
        // 分割成左右两部分 Li Ri
        String left = binIP.substring(0, 32);
        String right = binIP.substring(32);
        // 定义 Li-1  Ri-1
        String beforeLeft;
        String beforeRight;
        // 16轮 Feistel 转换
        // Li=Ri-1    Ri=Li-1 ^ F(Ri-1, Ki)
        for (int i = 0; i < 16; i++) {
            beforeLeft = left;
            beforeRight = right;
            left = beforeRight;
            right = xor(beforeLeft, feistel(beforeRight, binKeys48[15 - i]));
//            System.out.println("第" + (i + 1) + "轮的解密结果为" + left + right);
        }
        // 最后一轮交换后得到结果
        String decryptionText = right + left;
        return fPReplace(decryptionText);
    }
}

