DATAS SEGMENT
　　buf db '12ADdf#gh592HKL*','$'
　　tp1 db 0;大写字母个数
　　tp2 db 0;小写字母个数
　　tp3 db 0;数字的个数
　　tp4 db 0;其他字符的个数

　　str1 db 'the number of big is:','$'
　　str2 db 'the number of small is:','$'
　　str3 db 'the number of number is:','$'
　　str4 db 'the number of other is:','$'
　　str5 db 0dH,0aH,'$';换行

DATAS ENDS

STACKS SEGMENT
　　;此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
　　ASSUME CS:CODES,DS:DATAS,SS:STACKS
　　START:
　　　　MOV AX,DATAS
　　　　MOV DS,AX

　　　　lea si, buf
　　　　mov cx, 16;设置循环次数

　　　　　again:
　　　　　　;字符串结尾，结束程序
　　　　　　cmp byte ptr[si],'&'
　　　　　　je exit

　　　　　　;0-9
　　　　　　cmp byte ptr[si],30h;小于30，其他字符加1
　　　　　　jb L1
　　　　　　cmp byte ptr[si],39h;大于39进一步比较
　　　　　　jbe L2

　　　　　　cmp byte ptr[si],41h
　　　　　　jb L1
　　　　　　cmp byte ptr[si],5AH
　　　　　　jbe L3

　　　　　　cmp byte ptr[si],61h
　　　　　　jb L1
　　　　　　cmp byte ptr[si],7AH
　　　　　　jbe L4


　　　　L1:
　　　　　　inc tp4
　　　　　　jmp L5
　　　　L2:
　　　　　　inc tp3
　　　　　　jmp L5
　　　　L3:
　　　　　　inc tp1
　　　　　　jmp L5
　　　　L4:
　　　　　　inc tp2
　　　　　　jmp L5
　　　　L5:
　　　　　　add si,1
　　　　　　loop again



　　　　;显示大写字母
　　　　lea dx,str1
　　　　mov ah,09h
　　　　int 21h

　　　　mov bl,tp1
　　　　call disp ;调用子程序

　　　　mov ah,09h
　　　　lea dx,str5
　　　　int 21h

　　　　;显示小写字母
　　　　lea dx,str2
　　　　mov ah,09h
　　　　int 21h

　　　　mov bl,tp2
　　　　call disp ;调用子程序

　　　　mov ah,09h
　　　　lea dx,str5
　　　　int 21h

　　　　;显示数字
　　　　lea dx,str3
　　　　mov ah,09h
　　　　int 21h

　　　　mov bl,tp3
　　　　call disp ;调用子程序

　　　　mov ah,09h
　　　　lea dx,str5
　　　　int 21h

　　　　;显示其他
　　　　lea dx,str4
　　　　mov ah,09h
　　　　int 21h

　　　　mov bl,tp4
　　　　call disp ;调用子程序

　　　　mov ah,09h
　　　　lea dx,str5
　　　　int 21h


　　　　exit:
　　　　　　MOV AH,4CH
　　　　　　INT 21H

　　disp PROC ;显示BX中的数
　　　　mov ch,4
　　　　roll:

　　　　　　mov cl,4
　　　　　　rol bx,cl
　　　　　　mov dl,bl
　　　　　　and dl,0fh
　　　　　　cmp dl,9
　　　　　　jbe next1
　　　　　　add dl,07h
　　　　next1:

　　　　　　 add dl,30h
　　　　　　mov ah,02h
　　　　　　int 21h
　　　　　　dec ch
　　　　　　jnz roll
　　　　RET
　　disp ENDP



CODES ENDS
　　END START