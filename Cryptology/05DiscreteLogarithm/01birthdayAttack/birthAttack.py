import math
import random


def getRandomList(n):
    """集合方式实现生成n个随机数"""
    numbers = []
    while len(numbers) < n:
        i = random.randint(0, 100)
        if i not in numbers:
            numbers.append(i)
    return numbers


def brithAttack(alpha, beta, p):
    sqrt_p = int(math.sqrt(p))
    # 初始化两个列表
    list_k_value = []
    list_l_value = []
    # 生成 sqrt(p) 长度的随机数集合
    list_k = getRandomList(sqrt_p)
    list_l = getRandomList(sqrt_p)
    # 生成 sqrt(p) 长度的
    for i in range(sqrt_p):
        # 计算出 alpha^k mod p并放入集合，同时在另一列表记录下k
        item_k = pow(alpha, list_k[i], p)
        list_k_value.append(item_k)
        # 计算出 beta * alpha^{-l} mod p 并放入集合,同时在另一列表记录下l
        item_l = beta * pow(alpha, -list_l[i], p) % p
        list_l_value.append(item_l)

    print(list_k_value)
    print(list_l_value)
    # 求出合集
    coincide = set(list_k_value) & set(list_l_value)
    print(coincide)
    if not coincide:
        print("集合为空")
        return False
    else:
        for same in coincide:
            k_index = list_k_value.index(same)
            l_index = list_l_value.index(same)
            k_value = list_k[k_index]
            l_value = list_l[l_index]
            x = k_value + l_value
            print(f"求出了x：{x % (p - 1)}")
        return True


if __name__ == '__main__':
    while True:
        if brithAttack(alpha=19, beta=298, p=521):
            break