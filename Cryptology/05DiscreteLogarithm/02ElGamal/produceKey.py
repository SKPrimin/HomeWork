import random


def gcd(a: int, b: int):
    """欧几里得算法求最大公约数"""
    while a != 0:
        a, b = b % a, a
    return b


def euler(n):
    """欧拉函数"""
    # 如果n是质数直接返回n-1
    if (n, 1) == 1:
        return n - 1
    m = 0
    for i in range(n):
        if gcd(i, n) == 1:
            m += 1
    return m


def getFirstPrimitiveRoot(p):
    """算出第一个本原根"""
    # 得到欧拉函数值m
    euler_n = euler(p)
    # 双循环
    for a in range(2, p):
        for m in range(2, p):
            # 第一个m满足a^m = 1 mod p 同时m = euler_n则a为第一个本原根
            if pow(a, m, p) == 1:
                # 如果最小的正幂a不为欧拉函数，进行下一轮循环
                if m == euler_n:
                    return a
                else:
                    break
    return False


def getAllPrimitiveRoot(p, first):
    """求得所有的原根"""
    primitiveRoot = []
    for i in range(p):
        # 若 i与p互素，即i是 p-1的简化剩余系一员
        if gcd(i, p - 1) == 1:
            # 将 原根 加入列表
            primitiveRoot.append(pow(first, i, p))
    return primitiveRoot


if __name__ == '__main__':
    p = 521
    firstp = getFirstPrimitiveRoot(p)
    pR = getAllPrimitiveRoot(p, firstp)
    print(pR)

    # 随机选择一个本原根g
    g = pR[random.randint(0, len(pR) - 1)]
    # 随机生成一个 x
    x = random.randint(1, p - 2)
    # 计算出 y = g^x mod p
    y = pow(g, x, p)

    print(f"公开(p,g,y)：{(p, g, y)}")
    print(f"秘密保存x ：{x}")
