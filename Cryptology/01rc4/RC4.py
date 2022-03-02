def setTableSK(tableKoriginal):
    # 初始化线性表 S
    tableS = [i for i in range(256)]
    # 先读入输入的字符，使用map全部转为整数类型，再列表化转为list格式
    tableK = [i for i in tableKoriginal * (int(256 / len(tableKoriginal)) + 1)]
    tableK = tableK[0:256]

    # 已经获得原始的 S，K表。现在⽤K表对S表进⾏初始置换
    j = 0
    for i in range(256):
        j = (j + tableS[i] + tableK[i]) % 256
        tableS[i], tableS[j] = tableS[j], tableS[i]
    return tableS


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


def getRC4(Key, Text, length):
    '''RC4异或过程'''
    for i in range(length):
        Text[i] = Key[i] ^ Text[i]
    return Text


if __name__ == "__main__":
    # 接收输入的明文与密钥
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
