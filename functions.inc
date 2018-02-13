$NOLIST

				;/////////This is where the grunt work is done... this file contains all the work////
				;/////////behind temperature conversions, the speaker, and the hex display///////////
				
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
	
; Send a character using the serial port
putchar:
    jnb TI, putchar
    clr TI
    mov SBUF, a
    ret

; Send a constant-zero-terminated string using the serial port
SendString:
    clr A
    movc A, @A+DPTR
    jz SendStringDone
    lcall putchar
    inc DPTR
    sjmp SendString
SendStringDone:
    ret			

Do_Something_With_Result:		
	;CONVERT TO TEMPERATURE
	mov x, Result
	mov x+1, Result+1
	mov x+2, #0
	mov x+3, #0
	load_y(45)
	lcall mul32
	load_y(100)
	lcall div32
	load_y(26)
	lcall add32
	mov a, x
	da a
	lcall hex2bcd
	;LCD DISPLAY
	Set_Cursor(1, 3)
	Display_BCD(bcd+1)					
	Set_Cursor(1, 5)
	Display_BCD(bcd)
	;PUTTY DISPLAY
	mov a, bcd+1
	swap a
	anl a, #0fh				;getting all the digits we need for putty...
	orl a, #30h				;upper digits contained in bcd+1 and lower in bcd+0
	lcall putchar
	mov a, bcd+1
	anl a, #0fh
	orl a, #30h
	lcall putchar
	mov a, bcd+0
	swap a
	anl a, #0fh
	orl a, #30h
	lcall putchar
	mov a, bcd+0
	anl a, #0fh
	orl a, #30h
	lcall putchar
	mov a, #'\r'
	lcall putchar
	mov a, #'\n'
	lcall putchar
ret


hexdisplay:
	mov dptr, #HEX_7SEG			;sending the bcd temp values to the correct segments
	mov a, bcd			
	anl a, #0x0f
	movc a, @a+dptr
	mov disp1, a
	mov a, bcd
	swap a
	anl a, #0x0f
	movc a, @a+dptr
	mov disp2, a	
	mov a, bcd + 1
	anl a, #0x0f
	movc a, @a+dptr
	mov disp3, a
	ret

beep:
setb TR0
lcall delay
clr TR0
ret
  
load_segments:
	mov c, acc.0
	mov SEGA, c
	mov c, acc.1
	mov SEGB, c
	mov c, acc.2
	mov SEGC, c
	mov c, acc.3
	mov SEGD, c
	mov c, acc.4
	mov SEGE, c
	mov c, acc.5
	mov SEGF, c
	mov c, acc.6
	mov SEGG, c
	mov c, acc.7
	mov SEGP, c
	ret  
	
delay:
	Wait_Milli_Seconds(#190) 
	
InitSerialPort:
    ; Since the reset button bounces, we need to wait a bit before
    ; sending messages, otherwise we risk displaying gibberish!
    mov R1, #222
    mov R0, #166
    djnz R0, $   ; 3 cycles->3*45.21123ns*166=22.51519us
    djnz R1, $-4 ; 22.51519us*222=4.998ms
    ; Now we can proceed with the configuration
	orl	PCON,#0x80
	mov	SCON,#0x52
	mov	BDRCON,#0x00
	mov	BRL,#BRG_VAL
	mov	BDRCON,#0x1E ; BDRCON=BRR|TBCK|RBCK|SPD;
    ret	
    
checkreset:
	buttonpress(RESET, noreset)
	ljmp escape
	noreset:
	ret    
	
$LIST	