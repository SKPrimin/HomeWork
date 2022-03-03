CODE SEGMENT
	ASSUME CS:CODE
	START: 
	MOV AL,3EH ;此处假设为 3EH
	MOV BL,AL
	MOV DL,AL
	MOV CL,4
	SHR DL,CL
	CMP DL,9
	JBE NEXT1
	ADD DL,7
	NEXT1: ADD DL,30H
	MOV AH,2
	INT 21H ;显示高位 ASCII 码
	MOV DL,BL
	AND DL,0FH
	CMP DL,9
	JBE NEXT2
	ADD DL,7
	NEXT2: ADD DL,30H
	MOV AH,2
	INT 21H ;显示低位 ASCII 码
	MOV AH,4CH
	INT 21H
CODE ENDS ;返回 DOS
	END START