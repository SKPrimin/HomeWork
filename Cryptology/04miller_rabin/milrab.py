def chooseA(n):
    """依照小组底座进行测试结论选出a的列表"""
    if n < 2_047:
        alist = [2]
    elif n < 1_373_653:
        alist = [2, 3]
    elif n < 9_080_191:
        alist = [31, 73]
    elif n < 25_326_001:
        alist = [2, 3, 5]
    elif n < 3_215_031_751:
        alist = [2, 3, 5, 7]
    elif n < 3_825_123_056_546_413_051:
        alist = [2, 3, 5, 7, 11, 13, 17, 19, 23]
    elif n < 318_665_857_834_031_151_167_461:
        alist = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
    elif n < 3_317_044_064_679_887_385_961_981:
        alist = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]
    else:
        print("数字过大，请更改")
        alist = [x for x in range(n) if x % 2 == 1]
    return alist


def getKM(n):
    m = n - 1
    k = 0
    # 当m为奇数时循环终止 求出 2^k m = n - 1
    while m % 2 == 0:
        m = m / 2
        k = k + 1
    print(f"k:{k},m:{m}")
    return k, int(m)


def getaMmodN(a, m):
    # pow函数自动计算 a^m mod n
    x = pow(a, m, n)
    print(f"a^m mod n:{x}")
    # 计算结果x = 1或 -1
    if x == 1 or x == -1:
        return True
    else:
        return False


def geta2rMmodN(a, k, m):
    """计算 a^{2^r m} mod n的值"""
    # r = [0, k-1]
    for r in range(0, k):
        rm2 = 2 ** r * m
        x = pow(a, rm2, n)
        print(f"a^(2^r m) mod n:{x}")
        # 如果 a^{2^r m} mod n = -1 ,则可能为素数，在已知a的情况下能确实
        # 计算机会取正数，因此此处应为 n-1
        if x == n - 1:
            return True
        # 如果 a^{2^r m} mod n = 1 则为合数 直接返回False
        elif x == 1:
            return False
    # 如果循环已经结束仍未返回值，判定合数，返回FALSE
    return False


if __name__ == '__main__':
    # n为全局变量，各函数均可使用
    n = 23456789
    # 找到n对应的 a列表
    alist = chooseA(n)
    print(f"确定a的候选列表为：{alist}")
    # 计算出k,m
    k, m = getKM(n)
    #
    isPrime = True
    # 将每一个a都带入运算
    for a in alist:
        if not getaMmodN(a=a, m=m):
            if not geta2rMmodN(a=a, k=k, m=m):
                print(f"{n}为合数")
                isPrime = False
                break
    if isPrime:
        print(f"{n}为素数")