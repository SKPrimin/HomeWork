import string
import hashlib
import sys
import time


def lookFor(passwdList, target):
    for a in "B":
        for b in passwdList:
            for c in passwdList:
                for d in passwdList:
                    for e in passwdList:
                        passwd = a + b + c + d + e
                        sha1 = hashlib.sha1(passwd.encode('utf-8'))
                        sys.stdout.write("\r %s" % (passwd))
                        if sha1.hexdigest() == target:
                            return passwd


if __name__ == '__main__':
    start = time.time()
    # 三选项 string.ascii_letters+string.digits+string.punctuation
    passwdAvailable = string.ascii_letters + string.digits  # 仅有数字英文的情况
    target = "4B58475789E60DBF1A28D638B556A938134644C8".lower()
    print(len(passwdAvailable))
    lookFor(passwdAvailable, target)
    end = time.time()
    print(f"\nUse time: {end - start} s")
