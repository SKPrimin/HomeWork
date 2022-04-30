import hashlib
import binascii


def compare(file1, file2, flag):
    # This python script is designed to print out the number of different bits between two files (file1 and file2).
    if flag:
        hash1 = hashlib.md5(file1.encode())
        hash2 = hashlib.md5(file2.encode())
    else:
        hash1 = hashlib.sha256(file1.encode())
        hash2 = hashlib.sha256(file2.encode())
    hashString1 = (hash1.hexdigest())
    hashString2 = (hash2.hexdigest())
    # Convert HEX string to binary
    file1Binary = bin(int(hashString1, 16))[2:]
    file2Binary = bin(int(hashString2, 16))[2:]
    numDifferentBits = 0
    for x in range(len(file1Binary)if len(file1Binary) < len(file2Binary)else len(file2Binary)):
        if int(file1Binary[x]) == int(file2Binary[x]):
            numDifferentBits += 1
    return numDifferentBits


file1 = "1234567"
file2 = "0234567"

md5num = compare(file1, file2, 1)
print("Same digits in   MD5  hashes are:", md5num,
      ",The proportion is ", 100*md5num/128, "%")


sha2num = compare(file1, file2, 0)
print("Same digits in SHA256 hashes are:", sha2num,
      ",The proportion is ", 100*sha2num/256, "%")
