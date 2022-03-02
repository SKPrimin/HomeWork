import gmpy2

alpha = 13
beta = 1508131
p = 1212

l = 7

invl = gmpy2.invert(l, p)
print(invl)
print(beta * pow(alpha, invl) % p)

print(beta * pow(alpha, -l, p) % p)
