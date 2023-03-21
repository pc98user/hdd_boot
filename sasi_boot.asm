;===========================================================
; sasi_boot.asm
;
; SASIハードディスクから起動する
;===========================================================
cpu		8086
bits		16

org		0100h
start:
		call	rom_init	; ROM初期化
		; SASIは初期化するとブートする

		; 起動できるデバイスがないとき
		retf

romsegs		dw	0000h, 0d400h
		dw	0000h, 0dc00h
		dw	0000h, 0d700h
		dw	0, 0

%include "printlib.inc"
%include "printreg.inc"
%include "rom_init.inc"
