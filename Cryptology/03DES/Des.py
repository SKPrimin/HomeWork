# IP置换表
import libnum

IP = [58, 50, 42, 34, 26, 18, 10, 2,
      60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6,
      64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1,
      59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5,
      63, 55, 47, 39, 31, 23, 15, 7
      ]
# 逆IP置换表
invIP = [40, 8, 48, 16, 56, 24, 64, 32,
         39, 7, 47, 15, 55, 23, 63, 31,
         38, 6, 46, 14, 54, 22, 62, 30,
         37, 5, 45, 13, 53, 21, 61, 29,
         36, 4, 44, 12, 52, 20, 60, 28,
         35, 3, 43, 11, 51, 19, 59, 27,
         34, 2, 42, 10, 50, 18, 58, 26,
         33, 1, 41, 9, 49, 17, 57, 25
         ]
# S盒中的S1盒
S1 = [14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
      0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
      4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
      15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
      ]
# S盒中的S2盒
S2 = [15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
      3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
      0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
      13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
      ]
# S盒中的S3盒
S3 = [10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
      13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
      13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
      1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
      ]
# S盒中的S4盒
S4 = [7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
      13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
      10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
      3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
      ]
# S盒中的S5盒
S5 = [2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
      14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
      4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
      11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
      ]
# S盒中的S6盒
S6 = [12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
      10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
      9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
      4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
      ]
# S盒中的S7盒
S7 = [4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
      13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
      1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
      6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
      ]
# S盒中的S8盒
S8 = [13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
      1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
      7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
      2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
      ]
# S盒
S = [S1, S2, S3, S4, S5, S6, S7, S8]
# P置换表
P_table = [16, 7, 20, 21, 29, 12, 28, 17,
           1, 15, 23, 26, 5, 18, 31, 10,
           2, 8, 24, 14, 32, 27, 3, 9,
           19, 13, 30, 6, 22, 11, 4, 25
           ]
# 置换选择1，将64位密钥减至56位
PC_1 = [57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
        ]
# 置换选择2，用于将循环左移和右移后的56bit密钥压缩为48bit
PC_2 = [14, 17, 11, 24, 1, 5,
        3, 28, 15, 6, 21, 10,
        23, 19, 12, 4, 26, 8,
        16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55,
        30, 40, 51, 45, 33, 48,
        44, 49, 39, 56, 34, 53,
        46, 42, 50, 36, 29, 32
        ]
# 扩展置换E，将32bit数据扩展为48bit
E_table = [32, 1, 2, 3, 4, 5,
           4, 5, 6, 7, 8, 9,
           8, 9, 10, 11, 12, 13,
           12, 13, 14, 15, 16, 17,
           16, 17, 18, 19, 20, 21,
           20, 21, 22, 23, 24, 25,
           24, 25, 26, 27, 28, 29,
           28, 29, 30, 31, 32, 1
           ]


# DES密钥扩展算法
def CreateKeys(key64):
    # 通过置换选择1，将64位密钥变成56位密钥
    key56 = [key64[PC_1[i] - 1] for i in range(56)]
    c0 = key56[:28]
    d0 = key56[28:]  # 将密钥分成两部分
    resultKeys = []
    # 生成每一轮的密钥
    for i in range(16):
        if i in (0, 1, 8, 15):  # 确定移位次数
            sfttm = 1
        else:
            sfttm = 2
        c0 = c0[sfttm:] + c0[:sfttm]
        d0 = d0[sfttm:] + d0[:sfttm]  # 循环左移
        cd = c0 + d0
        # 通过置换选择2，将56位变成48位密钥
        key48 = [cd[PC_2[j] - 1] for j in range(48)]
        key48 = ''.join(key48)  # 列表转成字符串
        resultKeys.append(key48)
    return resultKeys


# 初始置换与逆初始置换
def ipChange(bits, mode):  # mode=1表示初始置换，mode=2表示逆初始置换
    if mode == 1:
        table = IP
    else:
        table = invIP
    resultbits = [bits[table[i] - 1] for i in range(64)]
    resultbits = ''.join(resultbits)  # 列表转成字符串
    return resultbits


# 通过扩展置换表E，将32bit扩展成48bit
def Eextend(rbits32):
    rbits48 = [rbits32[E_table[i] - 1] for i in range(48)]
    rbits48 = ''.join(rbits48)  # 列表转成字符串
    return rbits48


# S盒代换,将48bit变成32bit
def Schange(rbits48):
    k = 0
    rbits32 = ''
    for i in range(0, 48, 6):
        bits6 = rbits48[i:i + 6]
        row = bits6[0] + bits6[5]  # 首位两位作为行
        row = int(row, 2)
        col = bits6[1:5]  # 中间四位作为列
        col = int(col, 2)
        ind = row * 16 + col
        bits4 = bin(S[k][ind])[2:]
        if len(bits4) < 4:
            bits4 = '0' * (4 - len(bits4)) + bits4  # 不足四位则补0
        k += 1
        rbits32 += bits4
    return rbits32


# P置换
def Pchange(rbits32):
    rbits32 = [rbits32[P_table[i] - 1] for i in range(32)]
    rbits32 = ''.join(rbits32)  # 列表转成字符串
    return rbits32


# 01比特字符串的异或
def xor(bit1, bit2):
    bitlen = len(bit1)
    xorres = int(bit1, 2) ^ int(bit2, 2)
    xorbits = bin(xorres)[2:]  # 去掉'0b'
    if len(xorbits) < bitlen:
        xorbits = '0' * (bitlen - len(xorbits)) + xorbits  # 长度不够则在前面补0
    return xorbits


# DES的F函数
def F_func(bits32, key48):
    Ebits = Eextend(bits32)  # 扩展置换
    xorbits = xor(Ebits, key48)  # 异或操作
    Sbits = Schange(str(xorbits))  # S盒代换
    Pbits = Pchange(Sbits)  # P盒置换
    return Pbits


# DES加密与解密
def DES(origbits, keys, mode):  # mode=True表示加密，mode=False表示解密
    if mode == True:
        # print('DES字符明文为：', origtxt)

        print('64bit明文：\t   ', origbits)
        origbits = ipChange(origbits, 1)  # 初始置换
        lbits = origbits[:32]
        rbits = origbits[32:]
        # 16轮Feistel
        for i in range(16):
            prelbits = lbits  # 上一轮的L0
            prerbits = rbits  # 上一轮的R0
            lbits = prerbits
            rbits = xor(prelbits, F_func(prerbits, keys[i]))
            print('第{}轮的加密结果为{}'.format(i + 1, lbits + rbits))
        # 32bit互换
        newbits = rbits + lbits
        newbits = ipChange(newbits, 2)  # 逆初始变换
        print('64bit密文：\t   ', newbits)
        newtxt = bin2str(newbits)
        # print('字符串密文为：',newtxt)
    else:
        # print('字符密文为：', origtxt)
        # origbits = str2bin(origbits)  # 字符串转成二进制
        print('64bit密文：\t   ', origbits)
        origbits = ipChange(origbits, 1)  # 初始置换
        lbits = origbits[:32]
        rbits = origbits[32:]
        # 16轮Feistel
        for i in range(16):
            prelbits = lbits  # 上一轮的L0
            prerbits = rbits  # 上一轮的R0
            lbits = prerbits
            rbits = xor(prelbits, F_func(prerbits, keys[15 - i]))
            print('第{}轮的解密结果为{}'.format(i + 1, lbits + rbits))
        # 32bit互换
        newbits = rbits + lbits
        newbits = ipChange(newbits, 2)  # 逆初始变换
        print('64bit明文：\t   ', newbits)
        newtxt = bin2str(newbits)
        # print('字符串明文为：', newtxt)
    return newbits


# 当一个bit出错时观察DES的加密结果
def observeDES(origbit, keys, mode):  # mode=True表示加密，mode=False表示解密
    resultbits = []
    if mode == True:
        # print('字符明文为：', origbit)
        origbits = str2bin(origbit)  # 字符串转成二进制
        print('64bit明文：\t\t   ', origbits)
        origbits = ipChange(origbits, 1)  # 初始置换
        lbits = origbits[:32]
        rbits = origbits[32:]
        # 16轮Feistel
        for i in range(16):
            prelbits = lbits  # 上一轮的L0
            prerbits = rbits  # 上一轮的R0
            lbits = prerbits
            rbits = xor(prelbits, F_func(prerbits, keys[i]))
            print('第{}轮的加密结果为{}'.format(i + 1, lbits + rbits))
            resultbits.append(lbits + rbits)
        # 32bit互换
        newbits = rbits + lbits
        newbits = ipChange(newbits, 2)  # 逆初始变换
        # print('64bit密文：\t   ',newbits)
        newbit = bin2str(newbits)
    else:
        # print('密文为：', origbit)
        origbits = str2bin(origbit)  # 字符串转成二进制
        print('64bit密文：\t\t   ', origbits)
        origbits = ipChange(origbits, 1)  # 初始置换
        lbits = origbits[:32]
        rbits = origbits[32:]
        # 16轮Feistel
        for i in range(16):
            prelbits = lbits  # 上一轮的L0
            prerbits = rbits  # 上一轮的R0
            lbits = prerbits
            rbits = xor(prelbits, F_func(prerbits, keys[15 - i]))
            print('第{}轮的解密结果为{}'.format(i + 1, lbits + rbits))
            resultbits.append(lbits + rbits)
        # 32bit互换
        newbits = rbits + lbits
        newbits = ipChange(newbits, 2)  # 逆初始变换
        print('64bit明文：\t', newbits)
        newbit = bin2str(newbits)
        print('字符串明文为：', newbit)
    return newbit, resultbits


# 电码本（ECB）模式
def ECB(origbin, keys, mode):  # mode=True表示加密，mode=False表示解密
    r = len(origbin) % 64
    if r != 0:
        origbin = origbin + '0' * (64 - r)  # 字符长度不是4的倍数则在后面补上空格
    newtxt = ''
    for i in range(0, len(origbin), 64):
        intxt = origbin[i:i + 64]
        outtxt = DES(intxt, keys, mode)
        newtxt = newtxt + outtxt
    return newtxt


# 密码分组链接模式（CBC）
def CBC(origbit, keys, iv, mode):  # mode=True表示加密，mode=False表示解密
    if mode == True:
        # 首先得到c1
        p1 = origbit[:64]
        intbit = xor(p1, iv)  # 第一轮与IV异或
        c1 = DES(intbit, keys, mode)  # c1是字符密文
        newbit = c1
        # 得到c2到cn
        for i in range(64, len(origbit), 64):
            p = origbit[i:i + 64]
            c1bits = c1
            intbit = xor(p, c1bits)
            c1 = DES(intbit, keys, mode)
            newbit += c1
        return newbit
    else:
        # 首先得到p1
        c1 = origbit[:64]
        outbit = DES(c1, keys, mode)
        p1bits = outbit
        p1 = xor(p1bits, iv)  # p1是字符明文
        newbit = p1
        # 得到p2到pn
        for i in range(64, len(origbit), 64):
            ci = origbit[i:i + 64]
            outbit = DES(ci, keys, mode)
            pibits = outbit
            c1bits = origbit[i - 64:i]
            pi = xor(pibits, c1bits)
            newbit += pi
        return newbit


# 观察当密文分组出错时，还原的明文有几个分组错误
def ObserveGroupError(origtxt, keys):
    pass


def str2bin(message):
    """将字符串转换为二进制"""
    # # 自定义编码方式
    # result = ''
    # for i in message:
    #     t = bin(ord(i))[2:]  # 字符转成ASCII，再转成二进制，并去掉前面的0b
    #     if len(t) % 16 != 0:  # 使用16位二进制表示一个字符
    #         comp = 16 - len(t) % 16
    #         t = '0' * comp + t  # 不够16位则补0
    #     result += t
    # return result

    # 调用libnum库的方式
    lnbits = libnum.s2b(message)
    surpluszero = len(lnbits) % 64
    return lnbits if surpluszero == 0 else lnbits + '0' * (64 - surpluszero)


#
def bin2str(bits):
    """二进制转回字符串"""
    # # 自定义方法
    # result = []
    # for i in range(0, len(bits), 16):
    #     tbit = bits[i:i + 16]  # 使用16位二进制表示一个字符
    #     c = chr(int(tbit, 2))
    #     result.append(c)
    # result = ''.join(result)
    # return result
    # 调用libnum.b2s转回字符串
    lnstr = str(libnum.b2s(bits))
    # 删去\x00,输出正确的格式
    lnstr = lnstr[2:-1].replace('\\x00','')
    return lnstr

if __name__=='__main__':
    file_path=input('请输入文件路径：')#text.txt
    print(file_path)
    with open(file_path, 'r',encoding='utf-8') as fp:
        origtxt = fp.read()
        key = input('请输入密钥')
        key64 = str2bin(key)
        keys = CreateKeys(key64)
        mode = int(input('你需要加密还是解密？（1加密，0解密）'))
        mode = bool(mode)
        mthd=int(input('你要使用ECB模式还是CBC模式？（1表示ECB，2表示CBC）'))
        if mthd==1:
            # 三元运算符 mode不为0时即加密时进行编码
            origbin = origtxt if  mode ==0 else str2bin(origtxt)
            newbinECB = ECB(origbin, keys, mode)
            # 三元运算符 mode为0时即解密时进行解码=
            newbinECB = bin2str(newbinECB) if mode == 0 else newbinECB
            with open('newECB.txt', 'w', encoding='utf-8') as outfile:
                outfile.write(newbinECB)
        else:
            # ivstr = '87654321'
            ivstr = input("请输入IV")
            # iv转二进制，并在长度过长时自动截取
            iv = str2bin(ivstr)[:64]
            # 三元运算符 mode不为0时即加密时进行编码
            origbin = origtxt if mode == 0 else str2bin(origtxt)
            newbinCBC = CBC(origbin, keys, iv, mode)
            # 三元运算符 mode为0时即解密时进行解码=
            newbinCBC = bin2str(newbinCBC) if mode == 0 else newbinCBC
            with open('newCBC.txt', 'w', encoding='utf-8') as outfile:
                outfile.write(newbinCBC)