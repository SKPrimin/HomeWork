import hashlib
import itertools

wordSet = [['Q', 'q', '@'], ['W', 'w'], ['%', '5'],
           ['(', '8', '['], ['=', '0', '}'], ['I', 'i'], ['N', 'n'], ['*', '+', '~']]

setGroup = list(itertools.product(
    wordSet[0], wordSet[1], wordSet[2], wordSet[3], wordSet[4], wordSet[5], wordSet[6], wordSet[7]))
for i in setGroup:
    for j in itertools.permutations(i, 8):
        if hashlib.sha1(''.join(j).encode('utf8')).hexdigest() == '67ae1a64661ac8b4494666f58c4822408dd0a3e4':
            print(''.join(j))
            exit(0)
