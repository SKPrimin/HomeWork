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


def find_string(submd5):
    value = random_string(20)
    md5 = hashlib.md5()
    md5.update(value.encode("utf-8"))
    md5value = md5.hexdigest()
    count = 0
    while md5value[:HEX_LEN] != submd5:
        value = random_string(20)
        md5 = hashlib.md5()
        md5.update(value.encode("utf-8"))
        md5value = md5.hexdigest()
        count += 1
        # 不想看动画就注释下一句 动画可能会影响速度 本句主要是测试使用
        # sys.stdout.write("\r %s %s %d" % (value, md5value, count))
    print("\rNumber of collisions:%d" % count)
    return value


if __name__ == '__main__':

    print("submd5:")
    submd5 = sys.stdin.readline()[:-1]
    print("[*]Proof of work:")
    print("\tMD5(key)[:%d]==%s" % (HEX_LEN, submd5))
    print("[+]Give me the key:")

    for _ in range(COLLISION_TIMES):
        value = find_string(submd5)
        md5 = hashlib.md5()
        md5.update(value.encode("utf-8"))
        md5value = md5.hexdigest()

        print("MD5( %s )==%s" % (value, md5value))

        if md5value[:HEX_LEN] != submd5:
            print("[-]Access Failed")
