DATA SEGMENT
	BUFF DB 255 DUP('?')
DATA ENDS
;定义缓冲区

EXT SEGMENT 
	MESS DB 'skprimin$'
EXT ENDS

CODE SEGMENT
ASSUME CS:CODE,DS:DATA,ES:EXT
START:
MOV AX,DATA
MOV DS,AX
MOV AX,EXT
MOV ES,AX

;向缓冲区输入字符串
LEA DX,BUFF
MOV AH,0AH
INT 21H

MOV CL,BUFF+1
LEA SI,BUFF+2
LEA DI,MESS

CLD
MOV BL,'0'

XY:INC BL
CMPSB
LOOPZ XY
;循环BL+1

JZ YES
MOV DL,BL
JMP XXXXXXXXXX
YES:MOV DL,'v'
XXXXXXXXXX:MOV AH,2
INT 21H
;显示字符

MOV AH,4CH
INT 21H
CODE ENDS
END START
