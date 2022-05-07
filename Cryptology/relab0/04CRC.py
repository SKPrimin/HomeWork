import binascii
import time

start = time.time()
crc_num = 0x05665E74
for i in range(0, 127):
    for j in range(0, 127):
        for k in range(0, 127):
            txt = chr(i) + chr(j) + chr(k)
            if binascii.crc32(bytes(txt, 'utf-8')) == crc_num:
                print(f"crc32 of {txt} is -> {hex(binascii.crc32(bytes(txt, 'utf-8')))}")
end = time.time()
print(f"Use time: {end - start} s")
