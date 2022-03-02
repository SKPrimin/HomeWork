import random

# 第一步公开的信息
p, g = 521, 186
# 秘密保存的x
x = 401
# 签署的信息m
m = 1914168


def gcd(a: int, b: int):
    """欧几里得算法求最大公约数"""
    while a != 0:
        a, b = b % a, a
    return b


# 选择k 使得 gcd(k,p-1)=1
while True:
    k = random.randint(0, p - 1)
    if gcd(k, p - 1) == 1:
        break

# 计算 r = g^k mod p
r = pow(g, k, p)
# 求 k^-1

# 扩展欧几里得算法求逆 ki即为最终需要的逆元
ai, bi = k, p - 1
ki, ti, xi, yi = 1, 0, 0, 1  # 初始化s,t,x2,y2
while bi:
    qi, ri = divmod(ai, bi)
    ai, bi = bi, ri  # 求最大公约数
    ki, ti, xi, yi = xi, yi, ki - qi * xi, ti - qi * yi  # 辗转相除

# s = k^{-1} * (m-xr) mod (p-1)
s = ki * (m - x * r) % (p - 1)

print(f"Alice签署的消息(m,r,s)：{(m, r, s)}")
