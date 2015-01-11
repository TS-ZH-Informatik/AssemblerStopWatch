;=====================================================================
; Interrupt Vektoren
;---------------------------------------------------------------------

;---------------------------------------------------------------------
; variable vector section
;---------------------------------------------------------------------
	.section	vector,ROMDATA
	.org	VECTOR_ADR

	.lword	dummy_int		; vector  0  BRK
	.lword	dummy_int		; vector  1
	.lword	dummy_int		; vector  2  /INT7
	.lword	dummy_int		; vector  3  /INT6
	.lword	dummy_int		; vector  4  /INT3
	.lword	dummy_int	; vector  5  Timer B5
	.lword	dummy_int		; vector  6  Timer B4
				;	   UART1 start/stop condition detection
				;	   Bus collision detection
	.lword	dummy_int		; vector  7  Timer B3
				;            UART0 start/stop condition detection
				;	   bus collision detection
	.lword	dummy_int		; vector  8  SI/O4
				;	   /INT5
	.lword	dummy_int		; vector  9  SI/O3
				;	   /INT4
	.lword	dummy_int		; vector 10  UART2 start/stop condition detection
				;	   Bus collision detection
	.lword	dummy_int		; vector 11  DMA0
	.lword	dummy_int		; vector 12  DMA1
	.lword	dummy_int		; vector 13  Key input interrupt
	.lword	dummy_int		; vector 14  A/D Converter
	.lword	dummy_int		; vector 15  UART2 transmit
				;	   NACK2
	.lword	dummy_int		; vector 16  UART2 receive
				;	   ACK2
	.lword	dummy_int		; vector 17  UART0 transmit
				;	   NACK0
	.lword	dummy_int		; vector 18  UART0 receive
				;	   ACK0
	.lword	dummy_int		; vector 19  UART1 transmit
				;	   NACK1
	.lword	dummy_int		; vector 20  UART1 receive
				;	   ACK1
	.lword	Timer_int		; vector 21  Timer A0
	.lword	dummy_int		; vector 22  Timer A1
	.lword	dummy_int		; vector 23  Timer A2
	.lword	dummy_int		; vector 24  Timer A3
	.lword	dummy_int		; vector 25  Timer A4
	.lword	dummy_int		; vector 26  Timer B0
	.lword	dummy_int		; vector 27  Timer B1
	.lword	dummy_int		; vector 28  Timer B2
	.lword	Button1_int		; vector 29  /Int0
	.lword	Button2_int		; vector 30  /Int1
	.lword	dummy_int		; vector 31  /Int2
	.lword	dummy_int		; vector 32  
	.lword	dummy_int		; vector 33  
	.lword	dummy_int		; vector 34 
	.lword	dummy_int		; vector 35 
	.lword	dummy_int		; vector 36
	.lword	dummy_int		; vector 37 
	.lword	dummy_int		; vector 38
	.lword	dummy_int		; vector 39
	.lword	dummy_int		; vector 40 
	.lword	dummy_int		; vector 41  DMA2
	.lword	dummy_int		; vector 42  DMA3
	.lword	dummy_int		; vector 43  UART5 start/stop condition detection
				;	   bus collision detection
				;	   CEC1
	.lword	dummy_int		; vector 44  UART5 transmit
				;	   NACK5
				;	   CEC2
	.lword	dummy_int		; vector 45  UART5 receive
				;	   ACK5
	.lword	dummy_int		; vector 46  UART6 start/stop condition detection
				;	   Bus collision detection
				;	   Real-time clock period
	.lword	dummy_int 	; vector 47  UART6 transmit
				;	   NACK6
				;	   Real-time clock compare
	.lword	dummy_int 	; vector 48  UART6 receive
				;	   ACK6
	.lword	dummy_int 	; vector 49  UART7 start/stop condition detection
				;	   Bus collision detection
				;	   Remote control 0
	.lword	dummy_int 	; vector 50  UART7 transmit
				;	   NACK7
				;	   Remote Control 1
	.lword	dummy_int 	; vector 51  UART7 receive
				;	   ACK7
	.lword	dummy_int 	; vector 52
	.lword	dummy_int 	; vector 53
	.lword	dummy_int 	; vector 54
	.lword	dummy_int 	; vector 55
	.lword	dummy_int 	; vector 56
	.lword	dummy_int 	; vector 57
	.lword	dummy_int 	; vector 58
	.lword	dummy_int 	; vector 59  I2C-bus interface interrupt
	.lword	dummy_int 	; vector 60
	.lword	dummy_int 	; vector 61  SCL/SDA interrupt
	.lword	dummy_int 	; vector 62
	.lword	dummy_int 	; vector 63


;---------------------------------------------------------------------
; fixed vector section
;---------------------------------------------------------------------
	.section	fvector,ROMDATA
	.org	0fffdcH

UDI:	.lword	dummy_int

OVER_FLOW:
	.lword	dummy_int

BRKI:	.lword	dummy_int

ADDRESS_MATCH:
	.lword	dummy_int

SINGLE_STEP:
	.lword	dummy_int

WDT:	.lword	dummy_int

DBC:
	.lword	dummy_int

NMI:
	.lword	dummy_int

RESET:	.lword	start


;=====================================================================
; ID code & Option function select register
;---------------------------------------------------------------------
; ID code check function
		.id "#FFFFFFFFFFFFFF"

; option function select register
		.ofsreg	0FFH