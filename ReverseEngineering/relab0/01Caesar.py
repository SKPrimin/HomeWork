from nltk.corpus import wordnet # if you check. Otherwise, delete

Converter = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
             'v', 'w', 'x', 'y', 'z']


def caeser(cipher: str, move: int):
    # 一律转为小写字母
    cipher = cipher.lower()
    decipher = ""
    for i in cipher:
        if i in Converter:
            decipher += Converter[(ord(i) - 97 + move) % 26]
        else:
            decipher += ' '

    return decipher


# if you check
def enCheck(decipher):
    """检查是否为英文"""
    words = decipher.split(" ")
    # 至少一半英文才能通过
    least = len(words) / 2
    for word in words:
        if wordnet.synsets(word):
            least -= 1
        if least < 0:
            return True
    return False


cipher = "mxud jxu idemi vqbb qdt jxu mxyju mydti rbem jxu bedu mebv tyui rkj jxu fqsa ikhlylui"
decipherList = []  # if you check
for i in range(26):
    decipher = caeser(cipher, i)
    print(f"Right shift {i}:\t{decipher}")
    decipherList.append(decipher)  # if you check

# if you check
for i, decipher in enumerate(decipherList):
    if enCheck(decipher):
        print(f"May Original Text Right Shift {i}".center(45, "*"))
        print(decipher)
