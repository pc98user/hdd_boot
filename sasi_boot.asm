;===========================================================
; sasi_boot.asm
;
; SASI ID=0のハードディスクから起動する
;===========================================================
cpu		8086
bits		16

ROMSEG		equ	0d700h

org		0100h
start:
		mov	ax, ROMSEG
		mov	es, ax

		cmp	byte [es:0009h], 55h
		jne	.exit
		cmp	byte [es:000ah], 0AAh
		jne	.exit

		call	ROMSEG:0000h
.exit:
		retf
