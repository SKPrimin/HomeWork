def rep_by_dict(aStr, dict_for_rep: dict):
    newStr = ''
    for i in aStr:
        if i in dict_for_rep.keys():
            newStr += dict_for_rep[i]
        else:
            newStr += i
    return newStr


cipher = '''qrlnp't xvpqb endkt. "qbbne lr sn cvir la bndk npr bqts mvrgr nx gnzptrb,"
 syr nbk lqp yqk tqvk, "syr tqlr gnzptrb syqs v npgr cqir la odnsyrd eyrp er mqdsrk xnd syr bqts svlr. 
yr eqt sydrr qpk syvdsa eyrp syr cdrqs gnzpgvb gyntr yvl sn lnzps syr vdnp sydnpr. 
q lqp cdnep evsy tnpt nx yvt nep, ars vp tnlr eqat tsvbb q ona. 
rcc yqk qp vppngrpgr sn yvl, q terrsprtt er qbb bnirk. jvbb syr ona evsyvp anz, v snbk yvl syr kqa v snnj tyvm xnd syr eqbb. 
vs sqjrt q lqp sn dzbr. qp qrcnp, pns qp rcc. jvbb syr ona qpk brs syr lqp or ondp." syr nbk lqp xrbs unp't xqgr. "anz qdr yqbx syr qcr syqs rcc eqt, qpk anzd nep ozdkrp vt q gdzrbrd npr, v xrqd. 
anz evbb yqir bvssbr una nx anzd gnllqpk, ozs v syvpj anz yqir syr tsdrpcsy vp anz sn kn syr syvpct syqs lzts or knpr. 
jvbb syr ona, unp tpne. evpsrd vt qblnts zmnp zt. jvbb syr ona qpk brs syr lqp or ondp." '''

decrypture_dict = {'r': 'e', 's': 't', 't': 's', 'y': 'h', 'q': 'a', 'v': 'i', 'k': 'd', 'o': 'b', 'd': 'r', 'e': 'w',
                   'c': 'g', 'b': 'l', 'l': 'm', 'p': 'n', 'n': 'o', 'a': 'y', 'z': 'u', 'g': 'c', 'x': 'f', 'j': 'k',
                   'i': 'v', 'm': 'p', 'u': 'j'}

print(rep_by_dict(cipher, decrypture_dict))

# 检测剩余
import string
alletter = list(string.ascii_lowercase)  # 全集
keys = list(decrypture_dict.keys())  # 已有的密文
values = list(decrypture_dict.values())  # 已有的原文
print("Remaining letter".center(45, '*'))
print("原文剩余："+str([item for item in alletter if not item in keys]))
print("密文剩余："+str([item for item in alletter if not item in values]))