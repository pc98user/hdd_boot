;===========================================================
;hdd_boot.asm
;
; SASI/SCSIハードディスクから起動する
;===========================================================
cpu		8086
bits		16

DAUA		equ	0a0h
SECSIZE		equ	512
LOADSEG		equ	1fe0h

org		0100h
start:
		call	rom_init	; ROM初期化
		jmp	load

romsegs		dw	0000h, 0d400h
		dw	0000h, 0dc00h
		dw	0000h, 0d700h
		dw	0, 0

load:
		xor	ax, ax		; システム共通域参照
		mov	ds, ax

		; IPLセクタ読み込み
		mov	bx, SECSIZE
		mov	cx, 0		; c=0
		mov	dh, 0		; h=0
		mov	dl, 0		; s=0
		mov	ax, LOADSEG
		mov	es, ax
		mov	bp, 0000h
		mov	al, DAUA
		mov	[0584h], al
		mov	ah, 06h
		int	1bh

		jnb	boot		; CF=0(no error)

read_error:	; 読み込み失敗
		push	cs
		pop	ds
		mov	si, msg_error
		call	puts
		mov	al, ah		; AH=BIOSエラーコード
		call	preg8
		mov	al, 0ah
		call	putc

		retf

boot:		; 読み込み成功
		push	cs
		pop	ds
		mov	si, msg_booting
		call	puts

		xor	ax, ax		; IPLはDS=0を前提としている
		mov	ds, ax

		jmp	LOADSEG:0000h	; IPLにジャンプ


msg_error	db	"Read error! AH=", 0
msg_booting	db	"Booting...", 0ah, 0

%include "printlib.inc"
%include "printreg.inc"
%include "rom_init.inc"
