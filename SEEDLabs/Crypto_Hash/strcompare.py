def compare(str1, str2):
    count = 0
    for i, k in enumerate(str1):
        if k == str2[i]:
            count += 1
    return count


md51 = "23cdc18507b52418db7740cbb5543e54"
md52 = "fd44ab5bab8736267e5cf97f3656af65"

md5num = compare(md51, md52)
print("Same digits in   MD5  hashes are:", md5num,
      ",The proportion is ", 100*md5num/len(md51), "%")

sha21 = "2634c3097f98e36865f0c572009c4ffd73316bc8b88ccfe8d196af35f46e2394"
sha22 = "9aa3e2eb837181d08ec76dbd861d044adad214d1baf487dbb45681ba671cdd62"

sha2num = compare(sha21, sha22)
print("Same digits in SHA256 hashes are:", sha2num,
      ",The proportion is ", 100*sha2num/len(sha21), "%")
