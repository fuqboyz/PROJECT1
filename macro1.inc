$NOLIST

CSEG

movebcd mac	
	mov a, %0
	swap a
	anl a, #0x0f
	orl a, #0x30
	lcall putchar
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

HEX_print_0 mac		;prints 0
	setb PINhexA
	setb PINhexB
	setb PINhexC
	setb PINhexD
	setb PINhexE
	setb PINhexF
	clr PINhexG
endmac

HEX_print_1 mac		;prints 1
	clr PINhexA
	setb PINhexB
	setb PINhexC
	clr PINhexD
	clr PINhexE
	clr PINhexF
	clr PINhexG
endmac

HEX_print_2 mac		;prints 2
	setb PINhexA
	setb PINhexB
	clr PINhexC
	setb PINhexD
	setb PINhexE
	clr PINhexF
	setb PINhexG
endmac

HEX_print_3 mac		;prints 3
	setb PINhexA
	setb PINhexB
	setb PINhexC
	setb PINhexD
	clr PINhexE
	clr PINhexF
	setb PINhexG
endmac

HEX_print_4 mac		;prints 4
	clr PINhexA
	setb PINhexB
	setb PINhexC
	clr PINhexD
	clr PINhexE
	setb PINhexF
	setb PINhexG
endmac

HEX_print_5 mac		;prints 5
	setb PINhexA
	clr PINhexB
	setb PINhexC
	setb PINhexD
	clr PINhexE
	setb PINhexF
	setb PINhexG
endmac

HEX_print_6 mac		;prints 6
	setb PINhexA
	clr PINhexB
	setb PINhexC
	setb PINhexD
	setb PINhexE
	setb PINhexF
	setb PINhexG
endmac

HEX_print_7 mac		;prints 7
	setb PINhexA
	setb PINhexB
	setb PINhexC
	clr PINhexD
	clr PINhexE
	clr PINhexF
	clr PINhexG
endmac

HEX_print_8 mac		;prints 8
	setb PINhexA
	setb PINhexB
	setb PINhexC
	setb PINhexD
	setb PINhexE
	setb PINhexF
	setb PINhexG
endmac

HEX_print_9 mac		;prints 9
	setb PINhexA
	setb PINhexB
	setb PINhexC
	setb PINhexD
	clr PINhexE
	setb PINhexF
	setb PINhexG
endmac

$LIST
