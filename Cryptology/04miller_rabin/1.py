import math
def relatively_prime(a,b): # a > b
    while b != 0:
        temp = b
        b = a%b
        a = temp
    if a==1:#b为1了，能整除了，有最大因子
        return True
    else:
        return False
def  millerRabin(num):
    num=(int)(num)
    if num%2 ==0:#能被2整除，肯定是合数,不能则是奇数，奇数可能是素数
        return False
    flag = True
    Subsquare = 0
    temp = num - 1# n-1起
    while True:#一直循环至为奇数
        temp = temp / 2  #temp存放m
        Subsquare += 1   #为k次
        if temp % 2 != 0:
            break
    b=[] # 存放所求整数（num）的原根
    count = 0
    for i in range(2,num-1):# g^(P-1) = 1 (mod P)
        if relatively_prime(num,i):
            b.append(i)
            count += 1
            if count == 5:# 控制检测次数
                break
    for i in b:
        two = 0
        while True:
            if (i**temp)**(2**two)%num == 1 or (i**temp)**(2**two)%num == num-1:
                flag = True
                break
            else:
                two += 1
                if two == Subsquare:
                    flag = False
                    break
        if flag == False:
            break # 如果存在一次不满足条件，则退出循环
    return flag
num = input(u"请输入要进行Miller-Rabin算法检测的数：")
if millerRabin(num):
    print (u"{0}大概率是素数".format(num))
else:
    print (u"{0}是合数 ".format(num))