; This program generates a PWM signal to drive
; a servo motor. The PWM duty cycle is controlled by 
; a potentiometer on the PSOC, whose value is 
; transmitted over serial communication. 

.org 00h       
    ljmp start 
          
; Timer 0 interrupt handler 
.org 000bh
T0ISR:
	lcall pwm   
	reti 
	
; Main program 	
.org 100h     
start:	
	; initialize serial communication 
	mov tmod, #21h      	; set timer 1 to auto reload, mode 2
							; and timer 0, mode 1 (16-bit, manual reload)
    mov tcon, #40h      	; run timer 1
    mov th1, #0fdh      	; set 9600 baud with xtal=11.059 MHz
    mov scon, #50h     	 	; set serial control reg for 8 bit data and mode 1 

	; set 8255 control word 
	mov dptr, #0fe13h 		; control word address
	mov a, #83h 			; use group A as output, group B as input
	movx @dptr, a 
	
	; initialize values
	mov R0, #245d
	mov R1, #193d 
	mov R3, #00h 

	; initialize timer and interrupt 
	; mov tmod, #01h 			
	setb tr0 				; use timer 0 
	mov ie, #82h 			; enable timer 0 overflow interrupt 
	mov a, R0 
	mov th0, a 
	mov tl0, #255d 
	
	loop:
		sjmp loop 
		
		
; PWM subroutine
pwm:
	; cpl P1.0 
	cjne R3, #01h, lo
	hi:
		mov a, R0
		mov th0, a 
		mov tl0, #255d 	
		mov a, #10h 		; send hi to PA.4
		mov R3, #00h 
		sjmp done_duty
	lo:
		mov a, R1
		mov th0, a 
		mov tl0, #255d 
		mov a, #00h 		; send low to PA.4 
		mov R3, #01h 
	done_duty:
		mov dptr, #0fe10h
		movx @dptr, a 		; send command to PA of 8255 
		jnb ri, done_pwm
	get_serial:
		; cpl P1.0 
		mov a, sbuf			; get character from sbuf and put it in the accumulator
		; mov P1, a 
		mov R0, a			; sets new duty cycle high 
		lcall get_low 
		mov R1, a 			; sets new duty cycle low  
		mov P1, a 
		clr ri
	done_pwm:
		ret 
		
; Get low subroutine
; Calculates TH0 low, returns in accumulator
get_low:
	mov a, #255d 		; 255-TH0 high 
	clr c 
	subb a, R0 
	mov R2, a  
	mov a, #72d 		; 72-answer 
	clr c 
	subb a, R2 
	mov R2, a 
	mov a, #255d 		; 255-answer 
	clr c 
	subb a, R2 
	ret 
		