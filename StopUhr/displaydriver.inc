;*********************************************************************
;     	***Display Driver for ACM0802C Series LCD Module***
;
;	Author:		Martin Burger
;	Date:		31.10.2014
;	Version:	1.2
;
;
;	1.2: Error in displayWriteChar corrected
;	
;	This driver is customized for the M16C65 Development-Board,
;	combined with the corresponding LCD-Display ACM0802C.
;	The Display is driven by a KS0066-Chip. 
;
;	The driver uses the internal Timer B5 to updating the
;	Display every 50 Milliseconds.
;	The Timer runs on Interrupt-Priority-Level 4
;
;	Interface/Functions:
;	displayInit		<->	Initializes the Display 
;	displaySetPos		<->	Line in R0H (0/1), Pos in R0L (0-7)
;	displayWriteString	<->	Startaddress in A0, Last Char = 0x0C
;	displayWriteChar	<->	Char in R0L
;	displayClearBuffer	<->	Clears the Buffer
;	displayForceUpdate	<->	Force Display update
;
;	Notes:
;	- Dont forget to set the I-Flag in the main-Program
;	- Timer-B5 is used by the Display
;	- Timer-B5 Interrupt has to be called in the vector-table
;		Interrupt-Vector-Name: "int_displayupdate"
;*********************************************************************


Display_RS				.btequ		p2_0
Display_E				.btequ		p2_1
Display_D7				.btequ		p2_7
Display_D6				.btequ		p2_6
Display_D5				.btequ		p2_5
Display_D4				.btequ		p2_4

DisplayTopAddress 		.equ		0800h
BufferLine1				.equ		DisplayTopAddress + 0
BufferLine2				.equ		DisplayTopAddress + 8
WriteBufferLine1		.equ		DisplayTopAddress + 16
WriteBufferLine2		.equ		DisplayTopAddress + 24
BufferWritePos			.equ		DisplayTopAddress + 32
BufferWriteLine			.equ		DisplayTopAddress + 33



;*********************************************************************
;     	***InitDisplay***
;	
;		Initializes the Display if nescessary.
;		
;		Needs no values set
;*********************************************************************	
displayInit:	
	mov.b #0F3h, pd2			;Init Port 2
	mov.b #00h, p2
	btst cwr
	jnz Init_DisplayEnd
	bset cwr
	push.b R0L
	push.w R3			
	mov.w #035, R3
	JSR Long_Wait				;Wait 35ms	
	mov.b #02h, R0L
	JSR Write_Half_Command	
	mov.b #02h, R0L
	JSR Write_Half_Command	
	mov.b #0Fh, R0L
	JSR Write_Half_Command	
	mov.w #01h,R3
	JSR Long_Wait	
	mov.b #00,R0L
	JSR Write_Half_Command	
	mov.b #0Ch,R0L
	JSR Write_Half_Command	
	mov.w #01h,R3
	JSR Long_Wait		
	mov.b #00h,R0L
	JSR Write_Half_Command	
	mov.b #01h,R0L
	JSR Write_Half_Command	
	mov.w #02h,R3
	JSR Long_Wait		
	mov.b #00h,R0L
	JSR Write_Half_Command	
	mov.b #06h,R0L
	JSR Write_Half_Command		
	mov.w #010h,R3
	JSR Long_Wait
	pop.w R3
	pop.b R0L
Init_DisplayEnd:
	JSR InitDisplayTimer
	RTS
	
;*********************************************************************
;     	***SetPos***
;	
;		Set the Cursor Position in the Buffer by Line and Pos
;		
;		Line in R0H (0/1) , Pos in R0L (0-7)
;*********************************************************************	
displaySetPos:
	cmp.b #02h,R0H
	jpz EndOfBufferPosition
	cmp.b #08h,R0L
	jpz EndOfBufferPosition
	mov.b R0H,BufferWriteLine
	mov.b R0L,BufferWritePos
EndOfBufferPosition:
	RTS
	
;*********************************************************************
;     	***WriteString***
;	
;		Writes a string to the Buffer. The last Character is defined
;		by 0x0C.
;		If any characters are written out of the Buffer-Boundries, the
;		characters get lost.
;		Position has to be set previously
;		
;		Startaddress in A0
;*********************************************************************	
displayWriteString:
	push.w A1	
	cmp.b #01h,BufferWriteLine
	jz WriteStringLine2
WriteStringLine1:
	mov.w #BufferLine1,A1
	add.b BufferWritePos,A1
	mov.b [A0],[A1]
	inc.w A0
	add.b #01h,BufferWritePos
	cmp.b #0Ch,[A0]
	jz WriteStringEnd
	cmp.b #08h,BufferWritePos
	jz WriteStringEnd
	jmp WriteStringLine1
WriteStringLine2:
	mov.w #BufferLine2,A1
	add.b BufferWritePos,A1
	mov.b [A0],[A1]
	inc.w A0
	add.b #01h,BufferWritePos
	cmp.b #0Ch,[A0]
	jz WriteStringEnd
	cmp.b #08h,BufferWritePos
	jz WriteStringEnd
	jmp WriteStringLine2
WriteStringEnd:
	pop.w A1
	RTS
	
;*********************************************************************
;     	***WriteChar***
;	
;		Writes a singel Char to the Buffer
;		Position has to be set previously
;		
;		R0L contains Character
;*********************************************************************	
displayWriteChar:
	push.w A0
	push.w R1
	cmp.b #08h,BufferWritePos
	jpz WriteCharEnd
	cmp.b #01h,BufferWriteLine
	jz WriteCharLine2
WriteCharLine1:
	mov.w #BufferLine1,A0
	mov.b BufferWritePos, R1L
	mov.b #00h,R1H	
	add.w R1,A0
	mov.b R0L,[A0]
	add.b #01h, BufferWritePos
	jmp WriteCharEnd
WriteCharLine2:
	mov.w #BufferLine2,A0
	mov.b BufferWritePos, R1L
	mov.b #00h,R1H	
	add.w R1,A0
	mov.b R0L,[A0]
	add.b #01h, BufferWritePos
WriteCharEnd:
	pop.w R1
	pop.w A0
	RTS
	
;*********************************************************************
;     	***ClearBuffer***
;	
;		Clears the Display Buffer. The Display will be cleared on the
;		next autoupdate or by calling ForceUpdate.
;		
;		Needs no values set
;*********************************************************************	
displayClearBuffer:
	push.w A0
	push.b R0L
	mov.w #BufferLine1,A0
	mov.b #0h,R0L
ClearBufferLoop:
	mov.b #020h,[A0]
	inc.w A0
	inc.b R0L
	cmp.b #016,R0L
	jnz ClearBufferLoop
	pop.b R0L
	pop.w A0	
	RTS
	
;*********************************************************************
;     	***ForceUpdate***
;	
;		Forces the Display to update it's Buffer.
;		
;		Needs no values set
;*********************************************************************	
displayForceUpdate:
	JSR CopyBufferToWriteBuffer
	JSR WriteBufferToDisplay
	JSR RestartDisplayTimer
	RTS
	
	
;*********************************************************************
;     	***display_int***
;	
;		Interrupt called by Timer B5.
;		This Interrupt updates the Display automatically.
;		Dont Call this Routine by yourself!
;*********************************************************************	
int_displayupdate:
	push.w A0
	push.w A1
	push.w R0
	mov.b #00h,R0L
	mov.w #BufferLine1,A0
	mov.w #WriteBufferLine1,A1
BufferDifferenceCheckLoop:
	cmp.b [A0],[A1]
	jnz	BufferDifferenceDetected
	inc.w A0
	inc.w A1
	inc.b R0L
	cmp.b #016,R0L
	jz int_displayupdateend	
	jmp BufferDifferenceCheckLoop
BufferDifferenceDetected:
	JSR CopyBufferToWriteBuffer
	JSR WriteBufferToDisplay	
int_displayupdateend:
	pop.w R0
	pop.w A1
	pop.w A0
	reit	


;*********************************************************************
;*********************************************************************
;*********************************************************************
;     	***Helper-Functions***
;	
;	The following Functions are dedicated to driver-internal use only
;*********************************************************************	
WaitWhileBusy:
	mov.w #02h,R3
	JSR Long_Wait
	RTS

Clear_Display:
	push.b R0L
	JSR WaitWhileBusy
	mov.b #01h, R0L
	JSR Write_Command
	pop.b R0L
	RTS
	
Return_Home:
	push.b R0L
	JSR WaitWhileBusy
	mov.b #02h,R0L
	JSR Write_Command
	pop.b R0L
	RTS
	
SetDisplayPosition:	;R0H = Line, R0L = Position
	cmp.b #02h,R0H
	jpz EndOfDisplayPosition
	cmp.b #08h,R0L
	jpz EndOfDisplayPosition
	cmp.b #01h,R0H
	jnz WritePositionCommand
	add.b #040h,R0L
WritePositionCommand:
	or.b #080h,R0L
	JSR Write_Command	
EndOfDisplayPosition:
	RTS
	
Write_Character:	;Data in R0L
	bset Display_RS
	JSR WaitWhileBusy
	JSR Write_Upper_Nibble
	JSR WaitWhileBusy
	JSR Write_Lower_Nibble
	;JSR Write_Upper_Nibble
	RTS

Write_Command:			;Data in R0L
	bclr Display_RS
	JSR WaitWhileBusy
	JSR Write_Upper_Nibble
	JSR WaitWhileBusy
	JSR Write_Lower_Nibble
	RTS

Write_Half_Command:		;Data in R0L
	JSR Short_Wait
	bclr Display_RS
	JSR WaitWhileBusy
	JSR Write_Lower_Nibble
	RTS
	
Write_Upper_Nibble: ;from R0L
	push.b R0H
	JSR Short_Wait
	bset Display_E
	JSR Short_Wait
	mov.b R0L, R0H
	and.b #0F0h, R0H
	and.b #0Fh, p2
	or.b R0H, p2
	JSR Short_Wait
	bclr Display_E
	JSR Short_Wait
	pop.b R0H
	RTS
	
Write_Lower_Nibble:	;from R0L
	push.b R0H
	JSR Short_Wait
	bset Display_E
	JSR Short_Wait
	mov.b R0L, R0H
	rot.b #04h, R0H
	and.b #0F0h, R0H
	and.b #0Fh, p2
	or.b R0H, p2
	JSR Short_Wait
	bclr Display_E
	JSR Short_Wait
	pop.b R0H
	RTS

Long_Wait:						;Put ms value in R3	
	push.w R0
	push.w R1
	mov.w #000h, R0
StartOfOuterIteration:
	cmp.w R3, R0				
	jpz EndOfOuterIteration		
	mov.w #0000h, R1			
StartOfInnerIteration:
	cmp.w #00A64h, R1			
	jpz EndOfInnerIteration		
	add.w #001h, R1				
	jmp StartOfInnerIteration	
EndOfInnerIteration:			
	add.w #001h, R0				
	jmp StartOfOuterIteration	
EndOfOuterIteration:
	pop.w R1
	pop.w R0					
	RTS

Short_Wait:
	push.b R0L
	mov.b #00h,R0L
Short_Wait_Start:
	nop
	inc.b R0L
	cmp.b #50h,R0L
	jnz Short_Wait_Start
	pop.b R0L
	RTS
	
CopyBufferToWriteBuffer:
	push.w A0
	push.w A1
	push.b R0L
	mov.b #0,R0L
	mov.w #BufferLine1, A0
	mov.w #WriteBufferLine1, A1
CopyBufferLineLoop:
	mov.b [A0],[A1]
	inc.w A0
	inc.w A1
	inc.b R0L
	cmp.b #16,R0L
	jnz CopyBufferLineLoop
	pop.b R0L
	pop.w A1
	pop.w A0
	RTS
	
WriteBufferToDisplay:
	push.w R0
	push.w A0
	mov.w #0000h,R0
	JSR SetDisplayPosition
	mov.w #WriteBufferLine1, A0
	mov.b #00h,R0H
WriteBufferLine1Loop:
	mov.b [A0],R0L
	JSR Write_Character
	inc.w A0
	inc.b R0H
	cmp.b #08h,R0H
	jnz WriteBufferLine1Loop
	mov.w #0100h,R0
	JSR SetDisplayPosition	
	mov.b #00h,R0H
WriteBufferLine2Loop:
	mov.b [A0],R0L
	JSR Write_Character
	inc.w A0
	inc.b R0H
	cmp.b #08h,R0H
	jnz WriteBufferLine2Loop
	pop.w A0
	pop.w R0
	RTS
	
RestartDisplayTimer:
	bclr tb5s
	mov.w #37500,tb5
	bset tb5s
	RTS

InitDisplayTimer:	
	mov.w #37500,tb5
	mov.b #80h,tb5mr
	mov.b #04h,tb5ic
	bset tb5s
	RTS
