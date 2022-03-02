#  Alice 的公钥
p, g, y = 521, 186, 156
# Alice签署的消息
m, r, s = 1914168, 364, 284
# 计算 v1 v2 并比较
v1 = pow(y, r, p) * pow(r, s, p) % p
v2 = pow(g, m, p)

print(f"v1:{v1},v2:{v2}")
if v1 == v2:
    print("验证成功，签名有效")
