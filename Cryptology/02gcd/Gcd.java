package com.origin.gcd;
//*2021/10/25 20:36 by SKPrimin *Describe:欧几里得算法，Gcd类

public class Gcd {
    int a, b;
    private int g, s = 1, t = 0, m, n; //此处使用私有变量，保护g,s,t

    public Gcd() { //空构造器
    }

    public Gcd(int a, int b) { //全参构造器
        this.a = a;
        this.b = b;
        m = a; //存储a,b以备不时之需
        n = b;
    }

    @Override
    public String toString() {
        return "Gcd{" +
                "a=" + m +
                ", b=" + n +
                ", g=" + g +
                ", s=" + s +
                ", t=" + t +
                '}';
    }

    static int getG(int a, int b) { //本处使用了静态类，即可以不用创建实例，直接 Gcd.getG(a,b)调用
        if (b == 0) { //mod(a,b) = 0,则 此时的a就是最大公约数
            return a;
        }
        int r = a % b; // 辗转相除法
        return getG(b, r); //递归
//    return b==0?a:getG(b,a%b); // 三元运算符版本,一行解决
    }

    void getGst() {
        int x = 0, y = 1, q, r, sy, ty;
        while (b != 0) { //辗转相除
            q = a / b; // 将 ab的整数倍存储起来
            r = a % b;// 将 ab的余数存储起来
            a = b;
            b = r;

            sy = s; //将 s,t原始值存储起来
            ty = t;
            s = x; // 辗转交换
            t = y;
            x = sy - q * x;
            y = ty - q * y;
        }
        g = a;
    }

    public int getS() { //s即逆元
        return s > 0 ? s : s + n; //如果算出的s小于0，就变为正数
    }
}


class Test {
    public static void main(String[] args) {
        Gcd gcd = new Gcd(23456, 987654);
        gcd.getGst();
        System.out.println(gcd.toString());

        //使用静态类可以直接调用
        System.out.println(Gcd.getG(23456, 987654));

        Gcd gcd2 = new Gcd(8787, 91919);
        gcd2.getGst();
        System.out.println(gcd2.getS());
    }
}