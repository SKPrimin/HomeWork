CODE SEGMENT
ASSUME CS:CODE
START:
MOV AL,10110100B
MOV CX,8
XUYI:
RCL AL,1
RCR AH,1
LOOP XUYI
MOV AL,AH
MOV AH,4CH
INT 21H
CODE ENDS
END START