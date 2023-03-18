;===========================================================
; レジスタ表示のサンプルプログラム
;===========================================================
cpu		8086
bits		16

org		0100h
start:
		call	pregall
		mov	al, 0ah
		call	putc
		call	pregall
		retf

%include "printlib.inc"
%include "printreg.inc"
