;*********************************************************************
;     	***Clock Driver for M16C65***
;
;	Author:		Martin Burger
;	Date:		1.11.2014
;	Version:	1.0
;	
;	This driver is customized for the M16C65 Development-Board.
;	It configures the Controller to 8MHz and multiplies via the
;	PLL to 24MHz.
;	All internal Peripherals run on 24MHz
;	Baseclock f1 for Timers is 24MHz
;
;	Usage:
;	run subroutine: clockInit
;	
;*********************************************************************

clockInit:
	bset prc0
	and.b #0dbh, plc0 		;Set PLL Register
	bset prc0
	or.b #093h, plc0
	bset prc0
	and.b #03Fh, cm0		;Set Clock Control Register 0
	bset prc0
	and.b #03Fh, cm1		;Set Clock Control Register 1
	bset prc0
	or.b #02h, cm1
	bset prc0
	and.b #0fdh, cm2		;Set Clock Control Register 2	
	RTS
	
