from Crypto.Cipher import DES

from Crypto.Util.Padding import pad, unpad

# Keys = {
#     'A': '1234567a', 'B': '1234567b', 'C': '1234567c', 'D': '1234567d',    'E': '1234567e',
#     'F': '1234567f', 'G': '1234567g', 'H': '1234567h', 'I': '1234567i',    'J': '1234567j'
# }
# data = "A|B|278942"
# user1, user2, N1 = data.split('|')
# kb = bytes(Keys[user2].encode())
# print(Keys[user2])
#
# Ks = 1000000000000000
# strtmp = pad(bytes(f"{Ks}|{user1}".encode()), 16)
# print(strtmp)
#
#
# print(kb)

# cipher = DES.new(kb, DES.MODE_ECB)
# encrypt_msg = cipher.encrypt(strtmp)
# print(encrypt_msg)
# print(encrypt_msg)
# print(str(encrypt_msg)[2:-1])

# encrypt_msg = "b'\xa0\x98>3\x98\x89\xd7\xb7K\xd0gI\x19h\x7fV'"
# encrypt_msg = encrypt_msg[2:-1]
# print(str(encrypt_msg))
#
# encrypt_msg = encrypt_msg.replace("\\x","")
# print(encrypt_msg)
# print(bytes(encrypt_msg.encode()))
# # print(bytes(encrypt_msg.encode()))
# #
# decipher = DES.new(kb, DES.MODE_ECB)
# msg_dec = decipher.decrypt(encrypt_msg)
# print(unpad(msg_dec, 16))

print(bytes("|".encode()))