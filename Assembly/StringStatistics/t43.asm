datas   segment
  letter   db   ?
  digit    db   ?
  other    db   ?
  string   label  byte
           max db 80 
           act db ?  
           str db 80 dup(?)
print   db  13,10,'Please enter the string:','$'
mess1   db  13,10, 'The total number of letter : ','$'
mess2   db  13,10,'The total number of digit  : ','$'
mess3   db  13,10,'The total number of other character : ','$'
datas   ends

code  segment
      assume  cs:code,ds:datas
start: push  ds
       sub  ax,ax
       push  ax
       mov   ax,datas
       mov   ds,ax
       mov   es,ax
       mov   letter,0
       mov   digit,0
       mov   other,0
       lea   dx,print
       mov   ah,09h  
       int   21h
       lea   dx,string
       mov   ah,0ah
       int   21h
       sub   ch,ch
       mov   cl,[string+1]
       lea   si,string+2
	   
digitseg: 
       mov   al,[si] ;数字判断，小于0为其他,0到9为数字
       cmp   al,'0'
       jb    otherseg
       cmp   al,'9'
       ja    letterseg    
       inc   digit
       jmp   loop1
	   
letterseg: 
       cmp   al,'A' ;大写字母判断，9之后，大于9，小于A为其他，A到Z为字母
       jb    otherseg   						
       cmp   al,'Z'
       ja    letter2seg 
       inc   letter
       jmp   loop1  
	   
letter2seg:  
       cmp   al,'a' ;小写字母判断，大于Z，小于a为其他，a到z为字母
       jb    otherseg
       cmp   al,'z'
       ja    otherseg
       inc   letter
       jmp   loop1
otherseg: 
       inc   other ;上文中未被识别出的字符均为其他
	   
loop1:  
       inc   si
       dec   cl
       cmp   cl,0
       jz    print1 
       jne   digitseg 
	   
print1:   
       lea   dx,mess1 ;输出mess1，字母
       mov   ah,09h
       int   21h
	   
       mov   al,letter 
       call  disp
	   
       lea   dx, mess2 ;输出mess2，数字
       mov   ah,09h
       int   21h
       mov   al,digit
       call  disp
	   
       lea   dx, mess3 ;输出mess3，其他
       mov   ah,09h
       int   21h
       mov   al,other
       call  disp
exit:
       mov  ah, 4ch
       int  21h
disp:                 						;十进制数形式显示AL中的内容.
       mov  ah, 0
       mov  bl, 10
       div  bl        						;div 无符号:div src 16位操作:商ax=(dx,ax)/src,余数dx
       add  al, 30h   						 ;比如说al=15h,即21，表示letter数量，然后，这个过程就是，ax=0015h(21),除以bl，bl值为10
       mov  dl, al     						 ;则除完了的结果为2余1，则ah=01,al=02,即ax=0102h;,那么al+30h即为表示该数字的ASCII码值，因为0的ASCII值为30h
       mov  bh, ah      					 ;则ax=0132h,dl=32,bh=01;
       mov  ah, 02h     					 ;显示输出dx,则显示32码对应的数字，2
       int  21h           
       mov  al, bh      						  ;把01给al,然后算出ASCII码，然后给dx，然后显示
       add  al, 30h
       mov  dl, al        
       mov  ah, 02h
       int  21h     
       ret
code   ends
       end   start