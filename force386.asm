;===========================================================
; force386.asm
;
; CPU判別フラグをi386以上に書き換える
; https://www.webtech.co.jp/company/doc/undocumented_mem/memsys.txt
;===========================================================
cpu		8086
bits		16

org		0100h

start:
		xor	ax, ax
		mov	ds, ax
		or	byte [0480h], 03h

;		mov	ah, 4Ch
;		mov	al, 00h
;		int	21h

		ret
