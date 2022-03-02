package com.des.demo;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;
import java.security.SecureRandom;
import java.util.Arrays;

/**
 * @author: SKPrimin
 * @date: 2021/12/6  23:25
 * @ClassName: DESTT
 * @Description: TODO
 */
public class DESTT {
    public static byte[] desCrypto(byte[] datasource, String password) {
        try {
            System.out.println(Arrays.toString(datasource));
            SecureRandom random = new SecureRandom();
            DESKeySpec desKey = new DESKeySpec(password.getBytes());
            //创建一个密匙工厂，然后用它把DESKeySpec转换成
            SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
            SecretKey securekey = keyFactory.generateSecret(desKey);
            //Cipher对象实际完成加密操作
            Cipher cipher = Cipher.getInstance("DES");
            //用密匙初始化Cipher对象
            cipher.init(Cipher.ENCRYPT_MODE, securekey, random);
            //现在，获取数据并加密
            //正式执行加密操作
            return cipher.doFinal(datasource);
        } catch (Throwable e) {
            e.printStackTrace();
        }
        return null;
    }

    public static byte[] decrypt(byte[] src, String password) throws Exception {
        // DES算法要求有一个可信任的随机数源
        SecureRandom random = new SecureRandom();
        // 创建一个DESKeySpec对象
        DESKeySpec desKey = new DESKeySpec(password.getBytes());
        // 创建一个密匙工厂
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
        // 将DESKeySpec对象转换成SecretKey对象
        SecretKey securekey = keyFactory.generateSecret(desKey);
        // Cipher对象实际完成解密操作
        Cipher cipher = Cipher.getInstance("DES");
        // 用密匙初始化Cipher对象
        cipher.init(Cipher.DECRYPT_MODE, securekey, random);
        // 真正开始解密操作
        return cipher.doFinal(src);
    }


}

class TestDD {
    public static void main(String[] args) {
        //待加密内容
        String str = "E01914168SKPrimin张丞";
        //密码，长度要是8的倍数
        String password = "12345678";
        byte[] result = DESTT.desCrypto(str.getBytes(), password);
        assert result != null;
        System.out.println("加密后内容为：" + new String(result));

        //直接将如上内容解密
        try {
            byte[] decryResult = DESTT.decrypt(result, password);
            System.out.println("加密后内容为：" + new String(decryResult));
        } catch (Exception e1) {
            e1.printStackTrace();
        }
    }
}