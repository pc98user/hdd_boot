;===========================================================
; scsi_boot.asm
;
; SCSI ID=0のハードディスクから起動する
;===========================================================
cpu		8086
bits		16

DAUA		equ	0a0h
SECSIZE		equ	512
LOADSEG		equ	1fe0h

org		0100h
start:
		mov	ax, 0d400h
		mov	es, ax
		call	0d400h:0000h

		xor	ax, ax
		mov	ds, ax
		mov	ax, LOADSEG
		mov	es, ax

		mov	ah, 06h
		mov	al, DAUA
		mov	[0584h], al
		mov	bx, SECSIZE
		mov	cx, 0		; c=0
		mov	dh, 0		; h=0
		mov	dl, 0		; s=0

		mov	bp, 0000h
		mov	si, bp

		int	1bh

		jmp	LOADSEG:0000h
