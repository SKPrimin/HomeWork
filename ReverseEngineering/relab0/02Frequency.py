import string
import re


def frequentCount(paragraph, isWord=True,minVal=0):
    """isWord 为 Treu 查单词，否则为字母。 minVal为 最低出现次数"""
    if isWord:
        aStr = paragraph.replace(',', ' ').replace('.', ' ').split()
    else:
        aStr = re.sub("[^a-z^A-Z^0-9]", "", paragraph)

    aList = []
    # 利用集合元素唯一性自动实现去重
    aSet = set()
    for s in aStr:
        aSet.add(s)
        aList.append(s)

    # 列表转为字典，统计出aSet中每个元素出现的次数
    aDict = {}
    for item in aSet:
        counter = aList.count(item)
        if counter >= minVal:  # 仅出现一次的去除
            aDict[item] = aList.count(item)

    # 将字典按照元素值进行逆序排序
    return dict(sorted(aDict.items(), key=lambda i: i[1], reverse=True))


cipher = '''qrlnp't xvpqb endkt. "qbbne lr sn cvir la bndk npr bqts mvrgr nx gnzptrb," syr nbk lqp yqk tqvk, 
"syr tqlr gnzptrb syqs v npgr cqir la odnsyrd eyrp er mqdsrk xnd syr bqts svlr. yr eqt sydrr qpk syvdsa eyrp syr 
cdrqs gnzpgvb gyntr yvl sn lnzps syr vdnp sydnpr. q lqp cdnep evsy tnpt nx yvt nep, ars vp tnlr eqat tsvbb q ona. rcc 
yqk qp vppngrpgr sn yvl, q terrsprtt er qbb bnirk. jvbb syr ona evsyvp anz, v snbk yvl syr kqa v snnj tyvm xnd syr 
eqbb. vs sqjrt q lqp sn dzbr. qp qrcnp, pns qp rcc. jvbb syr ona qpk brs syr lqp or ondp." syr nbk lqp xrbs unp't 
xqgr. "anz qdr yqbx syr qcr syqs rcc eqt, qpk anzd nep ozdkrp vt q gdzrbrd npr, v xrqd. anz evbb yqir bvssbr una nx 
anzd gnllqpk, ozs v syvpj anz yqir syr tsdrpcsy vp anz sn kn syr syvpct syqs lzts or knpr. jvbb syr ona, 
unp tpne. evpsrd vt qblnts zmnp zt. jvbb syr ona qpk brs syr lqp or ondp." '''

print("Each Word Frequency".center(45,"*"))
print(frequentCount(cipher,True,2))
print("Each Letter Frequency".center(45,"*"))
print(frequentCount(cipher, False,0))
