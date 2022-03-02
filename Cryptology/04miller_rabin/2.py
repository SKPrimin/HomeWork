import random

n = input("测数：")
n = int(n)
count = 0
temp = n
while 1:
    temp = temp / 2
    count = count + 1
    if temp % 2 != 0:
        break
temp = int(temp)
count = int(count)
a = random.randint(1, n - 1)
d = (a ** temp) % n
if d == 1 or d == -1:
    flag = 0
else:
    c = 0
    while c < count:
        c = c + 1
        if a ** ((2 ** c) * temp) % n == -1:
            flag = 0
            break
        elif a ** ((2 ** c) * temp) % n == 1:
            flag = 1
            break
        if c >= (count - 1):
            flag = 1
            break

if flag == 0:
    print("素数哦！")
else:
    print("不好意思，合数一个")
