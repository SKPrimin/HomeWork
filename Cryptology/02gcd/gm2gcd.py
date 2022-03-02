import gmpy2

'''
常用的库
gmpy2.mpz(n)初始化一个大整数
n=invert(m,phi)求mod phi的逆元
pow(m,e,n)求c^d mod n
gmpy2.is_prime(n) 素性检测
gmpy2.gcd(a,b)  欧几里得算法，最大公约数
gmpy2.gcdext(a,b)  扩展欧几里得算法
gmpy2.iroot(x,n) x开n次根
'''


def gcdext(a: int, b: int) -> (int, int, int):
    # 扩展欧几里得算法 tuple (g,s,t)
    s, t, x, y = 1, 0, 0, 1  # 初始化s,t,x2,y2
    while b:
        q, r = divmod(a, b)
        a, b = b, r  # 求最大公约数
        s, t, x, y = x, y, s - q * x, t - q * y  # 辗转相除
    # 返回元组(g,s,t)，使 g == a*s + b*t
    return a, s, t


def gcd(a: int, b: int):
    while a != 0:
        a, b = b % a, a
    return b


def invert(m, phi):
    _, mi, _ = gcdext(m, phi)
    return mi if mi > 0 else mi + phi


if __name__ == "__main__":
    a, b = map(int, input("请输入a,b").split())
    print(gcd(a, b))
    print(gcdext(a, b))

    m, phi = map(int, input("请输入m,phi").split())
    print(invert(m, phi))
