;------------------------------------------------------------------------
;                                                                       |
;   FILE        :Init_M16C65                                      |
;   DATE        :Sept 2011                                              |
;   DESCRIPTION :Template für M16C65 Uebungen an der Juventus           |
;   CPU GROUP   :M16C65                                                 |
;   Owner       :Clive Giovannini                                       |
;                                                                       |
;   Version: 1.0                                                        |
;                                                                       |
;------------------------------------------------------------------------

	.glb start


VECTOR_ADR	.equ	0ff000H	; INTERRUPT VECTOR ADDRESS definition
ROM_TOPADR	.equ	0a0000H	; ROM TOP ADDRESS definition
stack_top	.equ	0bf00h	; Start User Stack
istack_top	.equ	0bfa0h	; Interrupt Stack
	




;=====================================================================
; after reset,the program starts here
;---------------------------------------------------------------------
	.section	program,CODE
	.org	ROM_TOPADR
	
start:
	fset	u		;set stack pointer
	ldc	#stack_top,sp
	fclr	u
	ldc	#istack_top,sp	;set istack pointer
			
	ldintb	#VECTOR_ADR


;=====================================================================
; User Program starts here
; Initialisierung
;---------------------------------------------------------------------

; Initialisiere Reset Circuit (ab Seite 51)
;---------------------------------------------------------------------
;	mov.b #00000000b,prcr	;Protect Register


; Initialisiere Reset Circuit (ab Seite 54)
;---------------------------------------------------------------------
;	mov.b #00000000b,pm0	;Processor Mode Register 0
;	mov.b #00000000b,rstfr	;Reset Source Determine Register

; Initialisiere Voltage Dedection Circuit (ab Seite 70)
;---------------------------------------------------------------------
;	mov.b #00000000b,vcr1	;Voltage Detector 2 Flag Register
;	mov.b #00000000b,vcr2	;Voltage Detector Operation Enable Register
;	mov.b #00000000b,vwce	;Voltage Monitor Function Select
;	mov.b #00000000b,vd1ls	;Voltage Dedector 1 Level Select Register
;	mov.b #00000000b,vw0c	;Voltage Monitor 0 Circuit Register
;	mov.b #00000000b,vw1c	;Voltage Monitor 1 Circuit Register
;	mov.b #00000000b,vw2c	;Voltage Monitor 1 Circuit Register
	

; Initialisiere Clock Generation Circuit (ab Seite 93)
;---------------------------------------------------------------------
	bset prc0
	mov.b #11000000b,pm0	;Processor Mode Register 0
	mov.b #00010000b,cm0	;System Clock Control Register 0
	mov.b #00110000b,cm1	;System Clock Control Register 1
;	mov.b #00000000b,cm2	;Oscillation Stop Dedection Register
;	mov.b #00000000b,pclkr	;Peripheral Clock Select Register
;	mov.b #00000000b,plc0	;PLL Control Register 0
;	mov.b #00000000b,pm2	;Processor Mode Register 2
;	mov.b #00000000b,fra0	;40 MHz On-Chip Oscillator Control Register 0
	bclr prc0	

; Initialisiere Power Control (ab Seite 123)
;---------------------------------------------------------------------
;	mov.b #00000000b,fmr0	;Flash Memory Control Register 0
;	mov.b #00000000b,fmr2	;Flash Memory Control Register 2


; Initialisiere Processor Mode (ab Seite 145)
;---------------------------------------------------------------------
;	mov.b #00000000b,pm0	;Processor Mode Register 0
;	mov.b #00000000b,prg2c	;Program 2 Area Control Register
;	mov.b #00000000b,dbr	;Data Bank Register


; Initialisiere Bus Function (ab S. 152)
;---------------------------------------------------------------------
;	mov.b #00000000b,pm0	;Processor Mode Register 0
;	mov.b #00000000b,pm1	;Processor Mode Register 1
;	mov.b #00000000b,csr	;Chip Select Control Register
;	mov.b #00000000b,ewr	;External Area Recovery Cycle Control Register
;	mov.b #00000000b,ewc	;External Area Wait Control Expansion Register
;	mov.b #00000000b,cse	;Chip Select Expansion Control Register
;	mov.b #00000000b,fmr1	;Flash Memory Control Register 1

; Initialisiere Memory Space Expansion Function (ab S. 184)
;---------------------------------------------------------------------
;	mov.b #00000010b,pm1	;Processor Mode Register 1
;	mov.b #00100000b,dbr	;Data Bank Register
	

; Initialisiere Ports P0 bis P10 (ab S. 184)
;---------------------------------------------------------------------
; Initialisiere Port 0
;	mov.b #00000000b,pd0	;Port Direction Register
;	bset pu00			;Pull up Port P0_0 bis P0_3
;	bset pu01			;Pull up Port P0_4 bis P0_7
;	mov.b #00000000b,p0		;Port Register

; Initialisiere Port 1
;	mov.b #00000000b,pd1	;Port Direction Register
;	bset pu02			;Pull up Port P1_0 bis P1_3
;	bset pu03			;Pull up Port P1_4 bis P1_7
;	mov.b #00000000b,p1		;Port Register

; Initialisiere Port 2
;	mov.b #00000000b,pd2	;Port Direction Register
;	bset pu04			;Pull up Port P2_0 bis P2_3
;	bset pu05			;Pull up Port P2_4 bis P2_7
;	mov.b #00000000b,p2		;Port Register
	
; Initialisiere Port 3
;	mov.b #00000000b,pd3	;Port Direction Register
;	bset pu06			;Pull up Port P3_0 bis P3_3
;	bset pu07			;Pull up Port P3_4 bis P3_7
;	mov.b #00000000b,p3		;Port Register	
	
; Initialisiere Port 4
;	mov.b #00000000b,pd4	;Port Direction Register
;	bset pu10			;Pull up Port P4_3
;	bset pu11			;Pull up Port P4_4 bis P4_5
;	mov.b #00000000b,p4		;Port Register	

; Initialisiere Port 5
;	mov.b #00000000b,pd6	;Port Direction Register
;	bset pu12			;Pull up Port P5_0 bis P5_3
;	bset pu13			;Pull up Port P5_4 bis P5_7
;	mov.b #00000000b,p6		;Port Register

; Initialisiere Port 6
;	mov.b #00000000b,pd6	;Port Direction Register
;	bset pu14			;Pull up Port P6_0 bis P6_3
;	bset pu15			;Pull up Port P6_4 bis P6_7
;	mov.b #00000000b,p6		;Port Register

; Initialisiere Port 7
;	mov.b #00000000b,pd7	;Port Direction Register
;	bset pu16			;Pull up Port P7_0 bis P7_3
;	bset pu17			;Pull up Port P7_4 bis P7_7
;	mov.b #00000000b,p7		;Port Register

; Initialisiere Port 8
;	mov.b #00000000b,pd8	;Port Direction Register
;	bset pu20			;Pull up Port P8_0 bis P8_3
;	bset pu21			;Pull up Port P8_4 bis P8_7
;	mov.b #00000000b,p8		;Port Register

; Initialisiere Port 9
;	mov.b #00000100b,prcr	;PD9 Freigabe
;	mov.b #00000000b,pd9	;Port Direction Register
;	bset pu22			;Pull up Port P9_0 bis P9_3
;	bset pu23			;Pull up Port P9_4 bis P9_7
;	mov.b #00000000b,p9		;Port Register

; Initialisiere Port 10
;	mov.b #00000000b,pd10	;Port Direction Register
;	bset pu24			;Pull up Port P10_0 bis P10_3
;	bset pu25			;Pull up Port P10_4 bis P10_7
;	mov.b #00000000b,p10		;Port Register


;	mov.b #00000000b,pcr	;Port Control Register (S. 202)	
;	mov.b #00000000b,nmidf	;/NMI-/SD Digital Filter Register (S. 205)

; Initialisiere Watchdog Timer
;------------------------------
;	mov.b #00000000b,vw2c	;Voltage Monitor 2 Control Register
;	mov.b #00010000b,cspr	;Count Source Protection Mode Register
;	mov.b #00000000b,wdtr	;Watchdog Timer Refresh Register
;	mov.b #00000000b,wdts	;Watchdog Timer Start Register
;	mov.b #00000000b,wdc	;Watchdog Timer Control Register	

; Initialisiere DMAC
;---------------------
;	mov.b #00000000b,sar0	;DMA0 Source Pointer
;	mov.b #00010000b,dar0	;DMA0 Destination Pointer
;	mov.b #00000000b,tcr0	;DMA0 Transfer Counter
;	mov.b #00000000b,dm0con	;DMA0 Control Register
;	mov.b #00000000b,sar1	;DMA1 Source Pointer
;	mov.b #00000000b,dar1	;DMA1 Destination Pointer
;	mov.b #00000000b,tcr1	;DMA1 Transfer Counter
;	mov.b #00000000b,dm1con	;DMA1 Control Register
;	mov.b #00010000b,sar2	;DMA2 Source Pointer
;	mov.b #00000000b,dar2	;DMA2 Destination Pointer
;	mov.b #00000000b,tcr2	;DMA2 Transfer Counter
;	mov.b #00000000b,dm2con	;DMA2 Control Register
;	mov.b #00000000b,sar3	;DMA3 Source Pointer
;	mov.b #00000000b,dar3	;DMA3 Destination Pointer
;	mov.b #00000000b,tcr3	;DMA3 Transfer Counter
;	mov.b #00010000b,dm3con	;DMA3 Control Register
;	mov.b #00000000b,dm2sl	;DMA2 Source Select Register
;	mov.b #00000000b,dm3sl	;DMA3 Source Select Register
;	mov.b #00000000b,dm0sl	;DMA0 Source Select Register
;	mov.b #00000000b,dm1sl	;DMA1 Source Select Register
	

; Initialisiere Timers
;---------------------------------------------------------------------	
;Timer A (S. 272 - 320)
;Initialisiere Timer A + B Count Source
;	mov.b #00000000b,pclkr	;Peripheral Clock Select Register
;	mov.b #00010000b,cpsrf	;Clock Prescaler Reset Flag
;	mov.b #00000000b,tckdivc0	;Timer AB Division Control Register 0
;	mov.b #00000000b,tabsr	;Count Start Flag
;	mov.b #00000000b,onsf	;One-Shot Start Flag
;	mov.b #00000000b,trgsr	;Trigger Select Register
;	mov.b #00000000b,udf	;Increment/Decrement Flag

;Initialisiere Timer A allgemein
;	mov.b #00000000b,pwmfs	;16-bit Pulse Width Modulation Mode Function Select Register
;	mov.b #00000000b,tapofs	;Timer A Waveform Output Function Select Register
;	mov.b #00000000b,taow	;Timer A Output Waveform Change Enable Register
	
; Initialisiere Timer A0 + A1
;	mov.b #00000000b,tacs0	;Timer A Count Source Select Register 0
;	mov.b #00000000b,ta0mr	;Timer A0 Mode Register
;	mov.b #00000000b,ta1mr	;Timer A1 Mode Register
;	mov.w #0ffffh,ta0		;Timer A0 Register
;	mov.w #0ffffh,ta1		;Timer A1 Register

;	mov.w #0ffffh,ta11		;Timer A1-1 Register

; Initialisiere Timer A2 + A3
;	mov.b #00000000b,tacs1	;Timer A Count Source Select Register 1
;	mov.b #00000000b,ta2mr	;Timer A2 Mode Register
;	mov.b #00000000b,ta3mr	;Timer A3 Mode Register
;	mov.w #0ffffh,ta2		;Timer A2 Register
;	mov.w #0ffffh,ta3		;Timer A3 Register
	
;	mov.w #0ffffh,ta21		;Timer A2-1 Register
	
; Initialisiere Timer A4	
;	mov.b #00000000b,tacs2	;Timer A Count Source Select Register 2
;	mov.b #00000000b,ta4mr	;Timer A4 Mode Register
;	mov.w #0ffffh,ta4		;Timer A4 Register
;	mov.w #0ffffh,ta41		;Timer A4-1 Register

	
; Initialisiere Timer B (S. 321 - 153)
;	mov.w #00000h,tb01		;Timer B0-1 Register
;	mov.w #00000h,tb11		;Timer B1-1 Register
;	mov.w #00000h,tb21		;Timer B2-1 Register	
;	mov.b #00000000b,ppwfs1	;Pulse Period/Pulse Width Measurement Mode Function Select Register 1

;	mov.b #00000000b,tbcs0	;Timer B Count Source Select Register 0
;	mov.b #00000000b,tbcs1	;Timer B Count Source Select Register 1
;	mov.b #00000000b,tb31	;Timer B3-1 Register
;	mov.b #00000000b,tb41	;Timer B4-1 Register
;	mov.b #00000000b,tb51	;Timer B5-1 Register
;	mov.b #00000000b,ppwfs2	;Pulse Period/Pulse Width Measurement Mode Function Select Register 2
;	mov.b #00000000b,tbcs2	;Timer B Count Source Select Register 2
;	mov.b #00000000b,tbcs3	;Timer B Count Source Select Register 3
;	mov.b #00000000b,tbsr	;Timer B3/B4/B5 Count Start Flag
;	mov.w #00000h,tb3		;Timer B3 Register
;	mov.w #00000h,tb4		;Timer B4 Register
;	mov.w #00000h,tb5		;Timer B5 Register
;	mov.b #00000000b,tb3mr	;Timer B3 Mode Register
;	mov.b #00000000b,tb4mr	;Timer B4 Mode Register
;	mov.b #00000000b,tb5mr	;Timer B5 Mode Register
;	mov.w #00000h,tb0		;Timer B0 Register
;	mov.w #00000h,tb1		;Timer B1 Register
;	mov.w #00000h,tb2		;Timer B2 Register	
;	mov.b #00000000b,tb0mr	;Timer B0 Mode Register
;	mov.b #00000000b,tb1mr	;Timer B1 Mode Register
;	mov.b #00000000b,tb2mr	;Timer B2 Mode Register	

; Three-Phase Motor Control Timer Function
;	mov.b #00000000b,tprc	;Three-Phase Protect Control Register
;	mov.w #00000h,ta11		;Timer A1-1 Register
;	mov.w #00000h,ta21		;Timer A2-1 Register
;	mov.w #00000h,ta41		;Timer A4-1 Register	
;	mov.b #00000000b,invc0	;Three-Phase PWM Control Register 0
;	mov.b #00000000b,invc1	;Three-Phase PWM Control Register 1
;	mov.b #00000000b,idb0	;Three-Phase Output Buffer Register 0
;	mov.b #00000000b,idb1	;Three-Phase Output Buffer Register 1
;	mov.b #00000000b,dtt	;Dead Time Timer
;	mov.b #00000000b,ictb2	;Timer B2 Interrupt Generation Frequency Set Counter
;	mov.b #00000000b,pdrf	;Position-Data-Retain Function Control Register
;	mov.b #00000000b,pfcr	;Port Function Control Register
;	mov.w #00000h,ta1		;Timer A1 Register
;	mov.w #00000h,ta2		;Timer A2 Register
;	mov.w #00000h,ta4		;Timer A4 Register
;	mov.w #00000h,tb2		;Timer B2 Register
;	mov.w #00000h,tb2sc		;Timer B2 Special Mode Register

	
; Initialisiere Real Time Clock (S. 388 - xxx)
;	mov.b #00000000b,rtcsec	;Real-Time Clock Second Data Register
;	mov.b #00000000b,rtcmin 	;Real-Time Clock Minute Data Register
;	mov.b #00000000b,rtchr	;Real-Time Clock Hour Data Register
;	mov.b #00000000b,rtcwk	;Real-Time Clock Day Data Register
;	mov.b #00000000b,rtccr1 	;Real-Time Clock Control Register 1
;	mov.b #00000000b,rtccr1 	;Real-Time Clock Control Register 2
;	mov.b #00000000b,rtccsr 	;Real-Time Clock Count Source Select Register
;	mov.b #00000000b,rtccsec 	;Real-Time Clock Second Compare Data Register
;	mov.b #00000000b,rtccmin 	;Real-Time Clock Minute Compare Data Register
;	mov.b #00000000b,rtcchr 	;Real-Time Clock Hour Compare Data Register

; Initialisiere Puls Width Modulator (S. 415 - xxx)	
;	mov.b #00000000b,pwmcon0	;PWM Control Register 0
;	mov.b #00000000b,pwmpre0 	;PWM0 Prescaler
;	mov.b #00000000b,pwmreg0 	;PWM0 Register

;	mov.b #00000000b,pwmcon1	;PWM Control Register 0
;	mov.b #00000000b,pwmpre1 	;PWM0 Prescaler
;	mov.b #00000000b,pwmreg1 	;PWM0 Register


; Initialisiere Remote Control Signal Receiver (S. 422 - xxx)
;------------------------------------------------------------
;	mov.b #00000000b,pmc0con0	;PMC0 Function Select Register 0
;	mov.b #00000000b,pmc0con1 	;PMC0 Function Select Register 1
;	mov.b #00000000b,pmc0con2 	;PMC0 Function Select Register 2
;	mov.b #00000000b,pmc0con3 	;PMC0 Function Select Register 3
;	mov.b #00000000b,pmc0sts	;PMC0 Status Register
;	mov.b #00000000b,pmc0int 	;PMC0 Interrupt Source Select Register
;	mov.b #00000000b,pmc0cpc 	;PMC0 Compare Control Register
;	mov.b #00000000b,pmc0cpd	;PMC0 Compare Data Register
;	mov.w #00000h,pmc0hdpmin 	;PMC0 Header Pattern Set Register (Min)
;	mov.w #00000h,pmc0hdpmax 	;PMC0 Header Pattern Set Register (Max)
;	mov.b #00000000b,pmc0d0pmin 	;PMC0 Data 0 Pattern Set Register (Min)
;	mov.b #00000000b,pmc0d0pmax 	;PMC0 Data 0 Pattern Set Register (Max)
;	mov.b #00000000b,pmc0d1pmin 	;PMC0 Data 1 Pattern Set Register (Min)
;	mov.b #00000000b,pmc0d1pmax 	;PMC0 Data 1 Pattern Set Register (Max)
;	mov.w #00000h,pmc0tim 	;PMC0 Measurements Register
;	mov.b #00000000b,pmc0dat0 	;PMC0 Receive Data Store Register 0
;	mov.b #00000000b,pmc0dat1 	;PMC0 Receive Data Store Register 1
;	mov.b #00000000b,pmc0dat2 	;PMC0 Receive Data Store Register 2
;	mov.b #00000000b,pmc0dat3 	;PMC0 Receive Data Store Register 3
;	mov.b #00000000b,pmc0dat4 	;PMC0 Receive Data Store Register 4
;	mov.b #00000000b,pmc0dat5 	;PMC0 Receive Data Store Register 5
;	mov.b #00000000b,pmc0rbit 	;PMC0 Receive Bit Count Register

; Initialisiere Serielle Schnittstellen (S. 469 - xxx)
;---------------------------------------------------------------------

;	mov.b #01000100b,pclkr	;Peripheral Clock Select Register
;	mov.b #01000100b,ucon	;UART Transmit/Receive Control Register 2
;	mov.b #01000100b,uclksel0	;UART Clock Select Register
	
; UART0 
;	mov.b #01000100b,u0smr4	;UART0 Special Mode Register 4
;	mov.b #01000100b,u0smr3	;UART0 Special Mode Register 3
;	mov.b #01000100b,u0smr2	;UART0 Special Mode Register 2
;	mov.b #01000100b,u0smr	;UART0 Special Mode Register
;	mov.b #01000100b,u0mr	;UART0 Transmit/Receive Mode Register 			
;	mov.b #00000000b,u0brg	;UART0 Bit Rate Register
;	mov.w #00000h,u0tb		;UART0 Transmit Buffer Register 
;	mov.b #00000000b,u0c0	;UART0 Transmit/Receive Control Register 0
;	mov.b #00000000b,u0c1	;UART0 Transmit/Receive Control Register 1
;	mov.w #00000h,u0rb		;UART0 Receive Buffer Register
	
; UART1 
;	mov.b #01000100b,u1smr4	;UART1 Special Mode Register 4
;	mov.b #01000100b,u1smr3	;UART1 Special Mode Register 3
;	mov.b #01000100b,u1smr2	;UART1 Special Mode Register 2
;	mov.b #01000100b,u1smr	;UART1 Special Mode Register
;	mov.b #01000100b,u1mr	;UART1 Transmit/Receive Mode Register 			
;	mov.b #00000000b,u1brg	;UART1 Bit Rate Register
;	mov.w #00000h,u1tb		;UART1 Transmit Buffer Register 
;	mov.b #00000000b,u1c0	;UART1 Transmit/Receive Control Register 0
;	mov.b #00000000b,u1c1	;UART1 Transmit/Receive Control Register 1
;	mov.w #00000h,u1rb		;UART1 Receive Buffer Register

; UART2 
;	mov.b #01000100b,u2smr4	;UART2 Special Mode Register 4
;	mov.b #01000100b,u2smr3	;UART2 Special Mode Register 3
;	mov.b #01000100b,u2smr2	;UART2 Special Mode Register 2
;	mov.b #01000100b,u2smr	;UART2 Special Mode Register
;	mov.b #01000100b,u2mr	;UART2 Transmit/Receive Mode Register 			
;	mov.b #00000000b,u2brg	;UART2 Bit Rate Register
;	mov.w #00000h,u2tb		;UART2 Transmit Buffer Register 
;	mov.b #00000000b,u2c0	;UART2 Transmit/Receive Control Register 0
;	mov.b #00000000b,u2c1	;UART2 Transmit/Receive Control Register 1
;	mov.w #00000h,u2rb		;UART2 Receive Buffer Register

; UART5 
;	mov.b #01000100b,u5smr4	;UART5 Special Mode Register 4
;	mov.b #01000100b,u5smr3	;UART5 Special Mode Register 3
;	mov.b #01000100b,u5smr2	;UART5 Special Mode Register 2
;	mov.b #01000100b,u5smr	;UART5 Special Mode Register
;	mov.b #01000100b,u5mr	;UART5 Transmit/Receive Mode Register 			
;	mov.b #00000000b,u5brg	;UART5 Bit Rate Register
;	mov.w #00000h,u5tb		;UART5 Transmit Buffer Register 
;	mov.b #00000000b,u5c0	;UART5 Transmit/Receive Control Register 0
;	mov.b #00000000b,u5c1	;UART5 Transmit/Receive Control Register 1
;	mov.w #00000h,u5rb		;UAR5 Receive Buffer Register

; UART6 
;	mov.b #01000100b,u6smr4	;UART6 Special Mode Register 4
;	mov.b #01000100b,u6smr3	;UART6 Special Mode Register 3
;	mov.b #01000100b,u6smr2	;UART6 Special Mode Register 2
;	mov.b #01000100b,u6smr	;UART6 Special Mode Register
;	mov.b #01000100b,u6mr	;UART6 Transmit/Receive Mode Register 			
;	mov.b #00000000b,u6brg	;UART6 Bit Rate Register
;	mov.w #00000h,u6tb		;UART6 Transmit Buffer Register 
;	mov.b #00000000b,u6c0	;UART6 Transmit/Receive Control Register 0
;	mov.b #00000000b,u6c1	;UART6 Transmit/Receive Control Register 1
;	mov.w #00000h,u6rb		;UART6 Receive Buffer Register
	
; UART7 
;	mov.b #01000100b,u7smr4	;UART7 Special Mode Register 4
;	mov.b #01000100b,u7smr3	;UART7 Special Mode Register 3
;	mov.b #01000100b,u7smr2	;UART7 Special Mode Register 2
;	mov.b #01000100b,u7smr	;UART7 Special Mode Register
;	mov.b #01000100b,u7mr	;UART7 Transmit/Receive Mode Register 			
;	mov.b #00000000b,u7brg	;UART7 Bit Rate Register
;	mov.w #00000h,u7tb		;UART7 Transmit Buffer Register 
;	mov.b #00000000b,u7c0	;UART7 Transmit/Receive Control Register 0
;	mov.b #00000000b,u7c1	;UART7 Transmit/Receive Control Register 1
;	mov.w #00000h,u7rb		;UART7 Receive Buffer Register

; Initialisiere Clock Synchrone Schnittstelle (S. 539 - xxx)
;	mov.b #00000000b,pclkr	;Peripheral Clock Select Register

; SI/O3
;	mov.b #00000000b,s3trr	;SI/O3 Transmit/Receive Register
;	mov.b #00000000b,s3c	;SI/O3 Control Register
;	mov.b #00000000b,s3brg	;SI/O3 Bit Rate Register

; SI/O4
;	mov.b #00000000b,s4trr	;SI/O4 Transmit/Receive Register
;	mov.b #00000000b,s4c	;SI/O4 Control Register
;	mov.b #00000000b,s4brg	;SI/O4 Bit Rate Register


; Initialisiere Multi-Master I2C Bus Interface (S. 553 - xxx)
;	mov.b #00000000b,pclkr	;Peripheral Clock Select Register
;	mov.b #00000000b,s00	;I2C0 Data Shift Register
;	mov.b #00000000b,s0d0	;I2C0 Address Register 0
;	mov.b #00000000b,s1d0	;I2C0 Control Register 0
;	mov.b #00000000b,s20	;I2C0 Clock Control Register 
;	mov.b #00000000b,s2d0	;I2C0 Start/Stop Condition Control Register
;	mov.b #00000000b,s3d0	;I2C0 Control Register 1
;	mov.b #00000000b,s4d0	;I2C0 Control Register 2
;	mov.b #00000000b,s10	;I2C0 Status Register 0
;	mov.b #00000000b,s11	;I2C0 Status Register 1
;	mov.b #00000000b,s0d1	;I2C0 Address Register 1
;	mov.b #00000000b,s0d2	;I2C0 Address Register 2	


; InitialisiereConsumer Electronics Control (CEC) Function (S. 603 - xxx)
;------------------------------------------------------------------------
;	mov.b #00000000b,cecc1	;CEC Function Control Register 1
;	mov.b #00000000b,cecc2	;CEC Function Control Register 2
;	mov.b #00000000b,cecc3	;CEC Function Control Register 3
;	mov.b #00000000b,cecc4	;CEC Function Control Register 4
;	mov.b #00000000b,cecflg	;CEC Flag Register
;	mov.b #00000000b,cisel	;CEC Interrupt Source Select Register
;	mov.b #00000000b,cctb1	;CEC Transmit Buffer Register 1
;	mov.b #00000000b,cctb2	;CEC Transmit Buffer Register 2
;	mov.b #00000000b,ccrb1	;CEC Receive Buffer Register 1
;	mov.b #00000000b,ccrb2	;CEC Receive Buffer Register 2
;	mov.b #00000000b,cradri1	;CEC Receive Follower Address Set Register 1
;	mov.b #00000000b,cradri2	;CEC Receive Follower Address Set Register 2
;	mov.b #00000000b,pcr	;Port Control Register

	
; Initialisiere A/D-Wandler (S. 637 - xxx)
;---------------------------------------------------------------------
;	mov.b #00000000b,pcr	;Port Control Register
;	mov.b #00000000b,ainrst	;Open-Circuit Detection Assist Function Register
;	mov.w #00000h,ad0		;A/D Register 0
;	mov.w #00000h,ad1		;A/D Register 1
;	mov.w #00000h,ad2		;A/D Register 2
;	mov.w #00000h,ad3		;A/D Register 3
;	mov.w #00000h,ad4		;A/D Register 4
;	mov.w #00000h,ad5		;A/D Register 5
;	mov.w #00000h,ad6		;A/D Register 6
;	mov.w #00000h,ad7		;A/D Register 7
;	mov.b #00000000b,adcon0	;A/D Control Register 0
;	mov.b #00000000b,adcon1	;A/D Control Register 1
;	mov.b #00000000b,adcon2	;A/D Control Register 2	



; Initialisiere Flash Memory Register (S. 679 - xxx)
;---------------------------------------------------------------------
;	mov.b #00000000b,fmr0	;Flash Memory Control Register 0
;	mov.b #00000000b,fmr1	;Flash Memory Control Register 1
;	mov.b #00000000b,fmr2	;Flash Memory Control Register 2
;	mov.b #00000000b,fmr6	;Flash Memory Control Register 6

	
	
; Initialisiere Interrupts (S. 106 - 108)
;---------------------------------------------------------------------
;	mov.b #00000000b,pm2	;Timer RE Interrupt Control Register

;	mov.b #00000000b,bcnic	;UART2 Bus Collision Detectetion Interrupt Control Reg
	
;	mov.b #00000000b,dm0ic	;DMA0 Interrupt Control Register
;	mov.b #00000000b,dm1ic	;DMA1 Interrupt Control Register
;	mov.b #00000000b,dm2ic	;DMA2 Interrupt Control Register
;	mov.b #00000000b,dm3ic	;DMA3 Interrupt Control Register	
	
;	mov.b #00000000b,ta0ic	;Timer A0 Interrupt Control Register
;	mov.b #00000000b,ta1ic	;Timer A1 Interrupt Control Register
;	mov.b #00000000b,ta2ic	;Timer A2 Interrupt Control Register
;	mov.b #00000000b,ta3ic	;Timer A3 Interrupt Control Register
;	mov.b #00000000b,ta4ic	;Timer A4 Interrupt Control Register

;	mov.b #00000000b,tb0ic	;Timer B0 Interrupt Control Register
;	mov.b #00000000b,tb1ic	;Timer B1 Interrupt Control Register
;	mov.b #00000000b,tb2ic	;Timer B2 Interrupt Control Register
;	mov.b #00000000b,tb3ic  	;Timer B3 Interrupt Control Register
		      ;u0bcnic	;UART0 Bus Collision Detection Interrupt Control Register
;	mov.b #00000000b,tb4ic  	;Timer B4 Interrupt Control Register
		      ;u1bcnic	;UART1 Bus Collision Detection Interrupt Control Register
;	mov.b #00000000b,tb5ic	;Timer B5 Interrupt Control Register

;	mov.b #00000000b,int0ic	;Ext. Int0 Interrupt Control Register
;	mov.b #00000000b,int1ic	;Ext. Int1 Interrupt Control Register
;	mov.b #00000000b,int2ic	;Ext. Int2 Interrupt Control Register
;	mov.b #00000000b,int3ic	;Ext. Int3 Interrupt Control Register
;	mov.b #00000000b,int4ic	;Ext. Int4 Interrupt Control Register
;	mov.b #00000000b,int5ic	;Ext. Int5 Interrupt Control Register
;	mov.b #00000000b,int6ic	;Ext. Int6 Interrupt Control Register
;	mov.b #00000000b,int7ic	;Ext. Int7 Interrupt Control Register
	
;	mov.b #00000000b,kupic	;Key Input Interrupt Control Register

;	mov.b #00000000b,adic	;A/D Conversion Interrupt Control Register
	
;	mov.b #00000000b,s0tic	;UART0 Transmit Interrupt Control Register
;	mov.b #00000000b,s0ric	;UART0 Receive Interrupt Control Register
;	mov.b #00000000b,s1tic	;UART1 Transmit Interrupt Control Register
;	mov.b #00000000b,s1ric	;UART1 Receive Interrupt Control Register
;	mov.b #00000000b,s2tic	;UART2 Transmit Interrupt Control Register
;	mov.b #00000000b,s2ric	;UART2 Receive Interrupt Control Register
;	mov.b #00000000b,s5tic   	;UART5 Transmit Interrupt Control Register
		      ;cec1ic	;CEC1 Interrupt Control Register
;	mov.b #00000000b,s5ric	;UART5 Receive Interrupt Control Register
;	mov.b #00000000b,u5bcnic   	;UART5 Bus Collision Detection Interrupt Control Register
		      ;pmc0ic	;Remote Control Signal Receiver 0 Interrupt Control Register
;	mov.b #00000000b,s6tic   	;UART6 Transmit Interrupt Control Register
		      ;rtccic	;Real-Time Clock Compare Interrupt Control Register
;	mov.b #00000000b,s6ric	;UART6 Receive Interrupt Control Register
;	mov.b #00000000b,u6bcnic   	;UART6 Bus Collision Detection Interrupt Control Register
		      ;rtctic	;Real-Time Clock Compare Interrupt Control Register
;	mov.b #00000000b,s7tic   	;UART7 Transmit Interrupt Control Register
		      ;pmc1ic	;Remote Control Signal Receiver 1 Interrupt Control Register
;	mov.b #00000000b,s7ric	;UART7 Receive Interrupt Control Register
;	mov.b #00000000b,u7bcnic   	;UART7 Bus Collision Detection Interrupt Control Register
		      ;pmc0ic	;Remote Control Signal Receiver 0 Interrupt Control Register

;	mov.b #00000000b,s3ic   	;SI/O3 Interrupt Control Register
		      ;int4ic	;INT4 Interrupt Control Register
;	mov.b #00000000b,s4ic   	;SI/O4 Interrupt Control Register
		      ;int5ic	;INT5 Interrupt Control Register
	
;	mov.b #00000000b,iicic	;I2C-bus Interface Interrupt Control Register
	
;	mov.b #00000000b,scldaic	;SCL/SDA Interrupt Control Register
	
;	mov.b #00000000b,ifsr	;Interrupt Source Select Register
;	mov.b #00000000b,ifsr2a	;Interrupt Source Select Register 2
;	mov.b #00000000b,ifsr3a	;Interrupt Source Select Register 3
	
;	mov.b #00000000b,aier	;Address Match Interrupt Enable Register
;	mov.b #00000000b,rmad0	;Address Match Interrupt Register 0
;	mov.b #00000000b,rmad1	;Address Match Interrupt Register 1
;	mov.b #00000000b,aier2	;Address Match Interrupt Enable Register 2
;	mov.b #00000000b,rmad2	;Address Match Interrupt Register 2
;	mov.b #00000000b,rmad3	;Address Match Interrupt Register 3
	
;	mov.b #00000000b,pcr	;Port Control Register
	
;	mov.b #00000000b,nmidf	;NMI/SD Digital Filter Register
		

;	fset i			;Enable all Interrupts


; Initialisierung Ende
;---------------------------------------------------------------------
jmp ProgramStart