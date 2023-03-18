;===========================================================
; fd_boot.asm
;
; FDからブートする(ドライブ選択可)
;===========================================================
cpu		8086
bits		16

DAUA		equ	90h
SECSIZE		equ	3	; 0=128Byte, 1=256Byte, 2=512Byte, 3=1024Byte
READLEN		equ	1024
LOADSEG		equ	1fc0h

org		0100h
start:
daua_input:
		push	cs
		pop	ds
		mov	si, msg_input
		call	puts

		xor	ax, ax
		mov	ds, ax

		mov	ah, 00h		; キー入力
		int	18h

		cmp	al, '1'
		jb	daua_input
		cmp	al, '4'
		ja	daua_input

		sub	al, '1'
		add	al, DAUA
		mov	[0584h], al

		mov	bx, READLEN
		mov	ch, SECSIZE
		mov	cl, 0		; c=0
		mov	dh, 0		; h=0
		mov	dl, 1		; s=1
		mov	ax, LOADSEG
		mov	es, ax
		mov	bp, 0000h
		mov	al, [0584h]
		mov	ah, 0d6h
		int	1bh

		jnb	boot		; CF=0(no error)

		push	cs
		pop	ds
		mov	si, msg_error
		call	puts
		mov	al, ah
		call	preg8
		mov	al, 0ah
		call	putc
		jmp	daua_input

boot:
		push	cs
		pop	ds
		mov	si, msg_booting
		call	puts

		xor	ax, ax
		mov	ds, ax

		jmp	LOADSEG:0000h


msg_input	db	"-- Input FD drive number (1-4) --", 0ah, 0
msg_error	db	"Read error! AH=", 0
msg_booting	db	"Booting...", 0ah, 0

%include "printlib.inc"
%include "printreg.inc"
