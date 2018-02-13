$NOLIST


				;//////////in this file there are five or six macros that are used during////////////////
				;//////////the interface initialization, as well as during the oven state machine////////



CSEG

movebcd mac	
	mov a, %0
	swap a
	anl a, #0x0f
	orl a, #0x30
	lcall putchar
endmac

displayvariable mac
    Set_Cursor(1,%0)
    Display_BCD(%1)
    Set_Cursor(1,%2)
    mov a, %3
    orl a, #0x30
	lcall ?WriteData
	endmac

increment1 mac
	mov a, %0
	cjne a, #0x99, done%md
	mov a, %1
	add a, #0x1
	da a
	mov %1, a
	done%md:
	mov a, %0
	add a, %2
	da a
	mov %0, a
endmac

increment5 mac
	mov a, %0
	cjne a, #0x95, done%md
	mov a, %1
	add a, #0x1
	da a
	mov %1, a
	done%md:
	mov a, %0
	add a, %2
	da a
	mov %0, a
endmac

buttonpress mac
   jb %0, sendback%md
   Wait_Milli_Seconds(#50)
   jb %0, sendback%md
   jnb %0, $
   sjmp done1%md
   
   sendback%md:
   ljmp %1
   done1%md:
endmac









$LIST