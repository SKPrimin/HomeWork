package com.origin.rc4;

/**
 * @author: SKPrimin
 * @date: 2021/10/17  14:24
 * @ClassName: TestRC4
 * @Description: TODO
 */
public class TestRC4 {
    public static void main(String[] args) {

        int[] dataoriginal = {1,2,3,4,5,6,7};
        int[] keyoriginal = {1,2,3};
        RC4 r = new RC4(dataoriginal, keyoriginal);
        r.mainRC4();
    }
}
