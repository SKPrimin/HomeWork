import re
import random

# 预加载常见弱密码项，使用集合自动去重
informationItem = set(["User", "root"])
characterItem = set(["!", "@", "#", "$", "%", "^",
                    "&", "*",  "_", ";", ".", ",", "/"])
weakItem = set(["123", "002", "456"])

with open("pass.txt") as f:
    passText = f.readlines()

print(passText)

for item in passText:

    data = item.replace("\n", "")
    try:
        # 信息项
        informationItem.add(re.findall(r"(^[A-Za-z0-9]+)", data)[0])
    except:
        print("ERROR"+data)
    try:
        # 符号项
        characterItem.add(re.findall(r"([\W_]+)", data)[0])
    except:
        print("ERROR"+data)
    try:
        # 弱字符项
        weakItem.add(re.findall(r"([A-Za-z0-9]+$)", data)[0])
    except:
        print("ERROR"+data)

print(informationItem)
print(characterItem)
print(weakItem)


def allPass():
    allPasswd = set()
    with open("passwdDict.txt", "w", encoding="utf-8") as fw:
        for i in informationItem:
            for c in characterItem:
                for w in weakItem:
                    fw.write(i+c+w+"\n")
    #                 allPasswd.add(i+c+w)
    # return allPasswd


def getInformation(v: list):
    item = random.choice(v)
    return item


def getCharacter(v: list):
    num = random.randint(1, 3)
    item = []
    for _ in range(num):
        chara = random.choice(v)
        item.append(chara)
        if len(chara) > 1:
            break
    return("".join(item))


def getWeak(v: list):
    item = random.choice(v)
    return item


def getPasswd():
    ifmt = getInformation(list(informationItem))
    chat = getCharacter(list(characterItem))
    weak = getWeak(list(weakItem))
    passwd = ifmt+chat+weak
    if len(passwd) < 6:
        getPasswd()
    else:
        return passwd


if __name__ == '__main__':
    # 生成所有密码
    allPass()

    # 随机生成弱密码
    for _ in range(10):
        print(getPasswd())
