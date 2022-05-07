import string


def Cutting(cipher, key_length):
    """据密钥长度对text进行分组,分组后为交织在一起的凯撒密码"""
    groups = ["" for _ in range(key_length)]
    for i, c in enumerate(cipher):
        groups[i % key_length] += c
    return groups


def countLetter(cipher):
    """统计26个字母各自 在参数text中 出现的次数"""
    # 初始化计数数组
    count = {}
    for i in string.ascii_uppercase:
        count[i] = 0
    for i in cipher:
        count[i] += 1
    return count


def cutAndCount(cipher, keyLength):
    """将前两个函数合并得到输出"""
    countOfGroup = []
    cipherGroups = Cutting(cipher, keyLength)
    for i in range(keyLength):
        countOfGroup.append(countLetter(cipherGroups[i]))
    # print([txtGroup, countOfGroup])
    return cipherGroups, countOfGroup


def calcIC(N: int, frequency):
    """在给定字母出现次数统计表的情况下计算重合指数"""
    IC = 0
    for i in string.ascii_uppercase:
        n_i = frequency[i]
        IC += (n_i * (n_i - 1))
    IC /= (N * (N - 1))
    return IC


def getAvgIC(keyLength, res, find):
    """得到在该长度下的组合重数平均值"""
    sumIC = 0
    for i in range(keyLength):
        N = len(res[i])
        found = find[i]
        sumIC += calcIC(N, found)
    return sumIC / keyLength


def getKey(keyLength, cipherGroup, find):
    """根据密钥长度猜测密钥 分组密钥的拟重合指数阈值 fi*pi/n（n是密文长度）"""
    key = ""
    for i in range(keyLength):  # 共keyLength组密文
        delta = 0  # 位移量
        # 最多26个字母
        for K in string.ascii_uppercase:
            IC = 0
            C_i = 65 + delta
            subCipher = cipherGroup[i]
            found = find[i]
            for p in probability:  # 根据拟重合指数公式，此处C_i所表示的字母是与英语的中第i个字母对应的
                if C_i == 91: C_i = 65
                IC += p * found[chr(C_i)]
                C_i += 1
            IC /= len(subCipher)
            # print(IC)  # 无结果时查看 调整 GROUP_IC
            if IC >= GROUP_IC:
                key += K
                break
            else:
                delta += 1
        # print("**********************************")# 无结果时查看
    if keyLength != len(key):
        key = None
    return key


def decrypt(key: str, cipher: str):
    """维吉尼亚密码解密"""
    decipher = ""
    keyLength = len(key)
    for i, c in enumerate(cipher):
        k = key[i % keyLength]
        origin = (ord(c) - ord(k)) % 26
        decipher += chr(origin + 65)
    return decipher


if __name__ == '__main__':
    # 分组密钥的拟重合指数阈值 标准英文中为0.067 可适当下降
    GROUP_IC = 0.06
    # 整体的平均重合指数阈值
    ALL_IC = 0.06
    # 单词频率表
    probability = [0.08167, 0.01492, 0.02782, 0.04253, 0.12705, 0.02228, 0.02015, 0.06094, 0.06996, 0.00153, 0.00772,
                   0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.0009, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978,
                   0.02360, 0.0015, 0.01974, 0.00074]
    cipher = "FPSLBRFRPWEASAPIJILVFAMHANKWPWGXHGEIKXZRFPSLIHVCJSGPSNQECXXMZILWPACAHLUKZAEIDEZWEQTDQTYTYATILWHEIGPQMQFKTONTGIDQEHDOSPMPQUMKFBVISIFZMLTIKBLCIMDDNEKWLXEMNWDACTITXIFSFIFCDVQUSAZIELSMOPUSEEFCPXDQWKFEJILJFMJLQSKJYXUTGFQOIDELQZGXFHVBSEEIUGZVZCNMZOSEAUEIZJECHHARKLPAUTDFAWREAPKBZAEPIXYGUXDWFOKWPGMAWAZPFXYXMAALIAJUTVEBHJQSVCEIPBGEQTYTCIIMJWFHITPTAAKANLVTITXIFSFIFCDSRBZWEETAFWUWFGDIERLVOMJSFIFCZJFPAKSEEIWIYIFAZAEDFXTWMKQOWWTWRILZQRJBLREQGFFHVGPAMALZQEOEWEZILAANKWLXTMOSEIEWTHUVYXARRRCMYMGJFHRISIIIKEMDRCOXTILLTEPLTWTMVLAAMDTHMVSKKLLBZVFPSLTEYPOWAUWVUSVPDIIPAUTCRJDIPPAKEEXGPKMBAGZITDFPPBZAZKFUYSABZWDAUTBYMBWKALLITSZALZQSVISIZPSVFOSTDMRBWVMNUQLPMVUWPAXPTREBWSOHFISID"
    minKeyLength = 5
    maxKeyLength = 15
    for keyLength in range(minKeyLength, maxKeyLength + 1):
        cipherGroups, countOfGroup = cutAndCount(cipher, keyLength)  # 得到分组
        avgIC = getAvgIC(keyLength, cipherGroups, countOfGroup)  # 计算平均重合重数
        # print(avgIC) # 无结果时查看，以便调整阈值
        if avgIC >= ALL_IC:
            key = getKey(keyLength, cipherGroups, countOfGroup)
            if key is not None:
                decipher = decrypt(key, cipher)
                print(f'猜测密钥长度 {keyLength} 可能存在密钥 {key} 解密得到明文: \n{decipher}\n小写格式\n{decipher.lower()}')
        else:
            print(f'猜测密钥长度 {keyLength} 无符合条件')