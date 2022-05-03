import sys
import random
import string
import hashlib

# 这是比对的位数，比对6*4=24位
HEX_LEN = 6
COLLISION_TIMES = 5


def random_string(length):
    strings = [random.choice(
        string.ascii_letters + string.digits + string.punctuation) for i in range(length)]
    return "".join(strings)


def getmd5(value):
    md5 = hashlib.md5()
    md5.update(value.encode("utf-8"))
    return md5.hexdigest()


def find_string():
    inp = random_string(20)
    md5value = getmd5(inp)
    inp2 = random_string(20)
    md5value2 = getmd5(inp2)
    count = 0
    while md5value[:HEX_LEN] != md5value2[:HEX_LEN]:
        inp = random_string(20)
        md5value = getmd5(inp)
        inp2 = random_string(20)
        md5value2 = getmd5(inp2)
        count += 1
        # 不想看动画就注释下一句 动画可能会影响速度 本句主要是测试使用
        # sys.stdout.write("\r %s %s %s %s %d" % (inp, md5value, inp2, md5value2, count))
    print("\rNumber of collisions:%d" % count)
    return inp, inp2


if __name__ == '__main__':
    print("[*]Proof of work:")
    print("\tMD5(key1)[:%d]==MD5(key2)[:%d]" % (HEX_LEN, HEX_LEN))
    print("[+]Give me the key:")

    for _ in range(COLLISION_TIMES):
        value1, value2 = find_string()
        md5value1 = getmd5(value1)
        md5value2 = getmd5(value2)

        print("MD5( %s )==%s\nMD5( %s )==%s" % (value1, md5value1, value2, md5value2))

        if md5value1[:HEX_LEN] != md5value2[:HEX_LEN]:
            print("[-]Access Failed")
