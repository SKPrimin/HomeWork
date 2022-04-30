import random
import string
import hashlib
HASH_VALUE = '021126'
numTrials = 0
times = 5
sumTrials = 0
for i in range(times):
    while True:
        randomStr = ''.join([random.choice(
            string.ascii_letters + string.digits + string.punctuation) for n in range(20)])
        hash_object = hashlib.md5(randomStr.encode())
        hash_string = hash_object.hexdigest()
        numTrials += 1
        if hash_string[0:6] == HASH_VALUE:
            break
    sumTrials += numTrials
    print("No.", i+1, "num trials to break one-way property = ", numTrials)
print("average:", sumTrials/times)
