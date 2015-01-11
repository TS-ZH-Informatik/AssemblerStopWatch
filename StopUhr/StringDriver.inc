;-------------------------------------------------
;	StringDriver
;
;	Date: 		17.11.2014
;	Written by: 	Martin Burger
;	Version: 	1.0
;
;	Little Driver to convert Numbers into
;	Strings.
;
;	Functions:
;	- UINT8ToString
;	- UINT16ToString
;	- SINT8ToString
;	- SINT16ToString
;-------------------------------------------------

StringDriverTopAddress	.equ		0700h
_SignedFlag				.equ		StringDriverTopAddress
_10kValue				.equ		StringDriverTopAddress +1
_1kValue				.equ		StringDriverTopAddress +2
_100Value				.equ		StringDriverTopAddress +3
_10Value				.equ		StringDriverTopAddress +4
_1Value					.equ		StringDriverTopAddress +5
_OrigValue				.equ		StringDriverTopAddress +6
_OrigAddress			.equ		StringDriverTopAddress +8



ClearStringDriverData:
	mov.b #0,_SignedFlag
	mov.b #0,_10kValue
	mov.b #0,_1kValue
	mov.b #0,_100Value
	mov.b #0,_10Value
	mov.b #0,_1Value
	mov.w #0,_OrigValue
	mov.w #0,_OrigAddress
	
	RTS

;R0L = Value, A0 = StringPos
UINT8ToString:
	PUSH.b R0H
	JSR ClearStringDriverData
	mov.b #0h,R0H
	mov.w R0,_OrigValue
	mov.w A0,_OrigAddress
	divu.b #10
	mov.b R0H, _1Value
	cmp.b #0h,R0L
	jz UI8Write
	mov.b #0h,R0H
	divu.b #10
	mov.b R0H, _10Value
	cmp.b #0h,R0L
	jz UI8Write
	mov.b R0L, _100Value
UI8Write:
	cmp.b #0h,_100Value
	jz UI8Write10
	mov.b _100Value,R0L
	add.b #'0',R0L
	mov.b R0L, [A0]
	inc.w A0
	jmp UI8Write10AlredyWritten
UI8Write10:
	cmp.b #0h,_10Value
	jz UI8Write1
UI8Write10AlredyWritten:
	mov.b _10Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
UI8Write1:
	mov.b _1Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	mov.b #0Ch,[A0]
	mov.w _OrigAddress, A0
	POP.b R0H
	RTS

;R0 = Value, A0 = StringPos	
UINT16ToString:
	PUSH.W R2
	PUSH.W R1
	JSR ClearStringDriverData
	mov.w #00h,R2
	mov.w R0,_OrigValue
	mov.w A0,_OrigAddress
	divu.w #10
	
	mov.w R2,R1
	mov.b R1L, _1Value
	cmp.w #0h,R0
	jz UI16Write
	mov.w #0h,R2
	divu.w #10
	
	mov.w R2,R1
	mov.b R1L, _10Value
	cmp.w #0h,R0
	jz UI16Write
	mov.w #0h,R2
	divu.w #10
	
	mov.w R2,R1
	mov.b R1L,_100Value
	cmp.w #0h,R0
	jz UI16Write
	mov.w #0h,R2
	divu.w #10
	
	mov.w R2,R1
	mov.b R1L,_1kValue
	cmp.w #0h,R0
	jz UI16Write
	mov.b R0L,_10kValue	
	
UI16Write:
	cmp.b #0h,_10kValue
	jz UI16Write1k
	mov.b _10kValue,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	jmp UI16Write1kAlredyWritten
UI16Write1k:
	cmp.b #0h,_1kValue
	jz UI16Write100
UI16Write1kAlredyWritten:
	mov.b _1kValue,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	jmp UI16Write100AlredyWritten
UI16Write100:
	cmp.b #0h,_100Value
	jz UI16Write10
UI16Write100AlredyWritten:
	mov.b _100Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	jmp UI16Write10AlredyWritten
UI16Write10:
	cmp.b #0h,_10Value
	jz UI16Write1
UI16Write10AlredyWritten:
	mov.b _10Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
UI16Write1:
	mov.b _1Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	mov.b #0Ch,[A0]
	mov.w _OrigAddress,A0

	POP.W R1
	POP.W R2
	RTS

;R0L = value, A0 = StringPos	
SINT8ToString:
	PUSH.b R0H
	JSR ClearStringDriverData
	mov.b #0h,R0H
	mov.w R0,_OrigValue
	mov.w A0,_OrigAddress
	btst 7,R0
	jz SI8NotSigned
	bset 0,_SignedFlag
	bclr 7,R0
	xor.b #07Fh,R0L
	inc.b R0L
SI8NotSigned:
	divu.b #10
	mov.b R0H, _1Value
	cmp.b #0h,R0L
	jz SI8Write
	mov.b #0h,R0H
	divu.b #10
	mov.b R0H, _10Value
	cmp.b #0h,R0L
	jz SI8Write
	mov.b R0L, _100Value
SI8Write:
	btst 0,_SignedFlag
	jz SI8WriteNotSigned
	mov.b #'-',[A0]
	inc.w A0		
SI8WriteNotSigned:
	cmp.b #0h,_100Value
	jz SI8Write10
	mov.b _100Value,R0L
	add.b #'0',R0L
	mov.b R0L, [A0]
	inc.w A0
	jmp SI8Write10AlredyWritten
SI8Write10:
	cmp.b #0h,_10Value
	jz SI8Write1
SI8Write10AlredyWritten:
	mov.b _10Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
SI8Write1:
	mov.b _1Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	mov.b #0Ch,[A0]
	mov.w _OrigAddress, A0
	POP.b R0H
	RTS
	
;R0 = value, A0 = StringPos	
SINT16ToString:
	PUSH.W R2
	PUSH.W R1
	JSR ClearStringDriverData
	mov.w #00h,R2
	mov.w R0,_OrigValue
	mov.w A0,_OrigAddress
	btst 15,R0
	jz SI16NotSigned
	bset 0,_SignedFlag
	bclr 15,R0
	xor.w #07FFFh,R0
	add.w #01h,R0
SI16NotSigned:	
	divu.w #10
	
	mov.w R2,R1
	mov.b R1L, _1Value
	cmp.w #0h,R0
	jz SI16Write
	mov.w #0h,R2
	divu.w #10
	
	mov.w R2,R1
	mov.b R1L, _10Value
	cmp.w #0h,R0
	jz SI16Write
	mov.w #0h,R2
	divu.w #10
	
	mov.w R2,R1
	mov.b R1L,_100Value
	cmp.w #0h,R0
	jz SI16Write
	mov.w #0h,R2
	divu.w #10
	
	mov.w R2,R1
	mov.b R1L,_1kValue
	cmp.w #0h,R0
	jz SI16Write
	mov.b R0L,_10kValue	
	
SI16Write:
	btst 0,_SignedFlag
	jz SI16WriteNotSigned
	mov.b #'-',[A0]
	inc.w A0	
SI16WriteNotSigned:
	cmp.b #0h,_10kValue
	jz SI16Write1k
	mov.b _10kValue,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	jmp SI16Write1kAlredyWritten
SI16Write1k:
	cmp.b #0h,_1kValue
	jz SI16Write100
SI16Write1kAlredyWritten:
	mov.b _1kValue,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	jmp SI16Write100AlredyWritten
SI16Write100:
	cmp.b #0h,_100Value
	jz SI16Write10
SI16Write100AlredyWritten:
	mov.b _100Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	jmp SI16Write10AlredyWritten
SI16Write10:
	cmp.b #0h,_10Value
	jz SI16Write1
SI16Write10AlredyWritten:
	mov.b _10Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
SI16Write1:
	mov.b _1Value,R0L
	add.b #'0',R0L
	mov.b R0L,[A0]
	inc.w A0
	mov.b #0Ch,[A0]
	mov.w _OrigAddress,A0

	POP.W R1
	POP.W R2
	RTS