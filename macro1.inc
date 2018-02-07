$NOLIST

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








forever:
    clr CE_ADC
	mov R0, #00000001B ; Start bit:1
	lcall DO_SPI_G
	mov R0, #10000000B ; Single ended, read channel 0
	lcall DO_SPI_G
	mov a, R1 ; R1 contains bits 8 and 9
	anl a, #00000011B ; We need only the two least significant bits
	mov Result+1, a ; Save result high.
	mov R0, #55H ; It doesn't matter what we transmit...
	lcall DO_SPI_G
	mov Result, R1 ; R1 contains bits 0 to 7. Save result low.
	setb CE_ADC
	lcall Delay
	
	;RETRIEVING TEMPERATURE OF OVEN
	lcall Do_Something_With_Result
	ret

$LIST