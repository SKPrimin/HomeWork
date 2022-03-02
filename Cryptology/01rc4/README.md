## 实验目的

理解流密码的概念及相关结构；

理解并能够编写基本的流密码体制；

熟练应用一种编程语言实现 RC4 密码算法体制。

## 基本原理

RC4 算法是一种序列密码体制或称流密码体制，其加密密钥和解密密钥相同 RC4 的密钥长度可变，但为了确保哪去安全强度，目前 RC4 至少使用 128 位的密钥。 

用 1~256 个字节（8~2048 位）的可变长度密钥初始化一个 256 个字节的状态向量S，S 的元素记为 S[0]，S[1],…,S[255]，从始至终置换后的 S 包含从 0 到 255 的所有8 位数。对于加密和解密，字节 K 是从 S 的 255 个元素中按一种系统化的方式选出的一个元素生成的。每生成一个 K 的值，S 中的元素个体就被重新置换一次。

RC4属于对称密码算法中的流密码加密算法。密钥⻓度可变，⾯向字节操作。分为初始化算法（KSA）伪随机子密码生成算法（PRGA)两大部分。它以⼀个⾜够⼤的表S为基础，对表进⾏⾮线性变换，产⽣密钥流。

明文$\bigoplus$密钥$\rightarrow$密文          密文$\bigoplus$密钥$\rightarrow$明文

## **加密过程**

1. 线性填充S表，⼀般为256个字节；并用种子密钥填充另⼀个256字节的K表，再用K表对S表进行初始置换

   ```python
   def setTableSK(tableKoriginal):
       # 初始化线性表 S
       tableS = [i for i in range(256)]
       
       tableK = [i for i in tableKoriginal * (int(256 / len(tableKoriginal)) + 1)]
       tableK = tableK[0:256]
   
       # 已经获得原始的 S，K表。现在⽤K表对S表进⾏初始置换
       j = 0
       for i in range(256):
           j = (j + tableS[i] + tableK[i]) % 256
           tableS[i], tableS[j] = tableS[j], tableS[i]
       return tableS
   ```

   

2. ⽣成密钥流（为每个待加密的字节⽣成⼀个伪随机数，⽤来异或）

   ```python
   def getKeyStream(tableS, KeyStream, length):
       '''生成密钥流（为每个待加密的字节⽣成⼀个伪随机数）'''
       i, j, t = 0, 0, 0
       for r in range(length):
           i = (i + 1) % 256
           j = (j + tableS[i]) % 256
           tableS[i], tableS[j] = tableS[j], tableS[i]
           t = (tableS[i] + tableS[j]) % 256
           KeyStream[r] = tableS[t]
       return KeyStream
   ```

   

3. 需要加密的字符与密钥抑或运算，明文$\bigoplus$密钥$\rightarrow$密文 

    ```python
    def getRC4(Key, Text, length):
        '''RC4异或过程'''
        for i in range(length):
            Text[i] = Key[i] ^ Text[i]
        return Text
    ```

4. 编写主函数使其能够处理各函数之间变量传递

   ```python
   if __name__ == "__main__":
       # 接收输入的明文与密钥。先读入输入的字符，使用map全部转为整数类型，再列表化转为list格式
       Dataoriginal = list(map(int, input("请输入明文").split()))
       Keyoriginal = list(map(int, input("请输入密钥").split()))
   
       # 初始化S表
       tableS = setTableSK(Keyoriginal)
       # 生成密钥流
       length = len(Dataoriginal)
       KeyStream = [0] * length
       KeyStream = getKeyStream(tableS, KeyStream, length)
       
       # 明文与密钥流异或运算加密
       Dataencryption = getRC4(KeyStream, Dataoriginal, length)
       print("已进行加密，加密结果为：{}".format(Dataencryption))
       # 密文与密钥流异或运算解密
       Dataendecryption = getRC4(KeyStream, Dataencryption, length)
       print("已进行解密，解密结果为：{}".format(Dataendecryption))
   ```

### 程序运行

截图

![image-20211017132117068](\RC4test.assets\image-20211017132117068.png)

### java 实现

```java
import java.util.Arrays;

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
```

```java
public class TestRC4 {
    public static void main(String[] args) {

        int[] dataoriginal = {1,2,3,4,5,6,7};
        int[] keyoriginal = {1,2,3};
        RC4 r = new RC4(dataoriginal, keyoriginal);
        r.mainRC4();
    }
}
```

![image-20211017144438771](RC4test.assets\image-20211017144438771.png)
