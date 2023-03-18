;===========================================================
; fd_boot.asm
;
; FD#3(DA/UA=92h)からブートする
;===========================================================
cpu		8086
bits		16

DAUA		equ	92h
SECSIZE		equ	1024
LOADSEG		equ	1fc0h

org		0100h
start:
		xor	ax, ax
		mov	ds, ax
		mov	ax, LOADSEG
		mov	es, ax

		mov	ah, 0d6h
		mov	al, DAUA
		mov	[0584h], al
		mov	bx, SECSIZE
		mov	ch, 3		; n=1024
		mov	cl, 0		; c=0
		mov	dh, 0		; h=0
		mov	dl, 1		; s=1

		mov	bp, 0000h
		mov	si, bp

		int	1bh

		jmp	LOADSEG:0000h
