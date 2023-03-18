;===========================================================
; printreg.inc
;
; レジスタ値表示ライブラリ
;===========================================================
;cpu		8086
;bits		16

; 4bit16進表示(private)
; 入力
;   AL=数値下1桁(0-F)
; 使用
;   AX,BX,DX(_putchar)
_preg4:
		and	al, 0fh
		cmp	al, 10
		jb	_p4010
		add	al, 'A'-'0'-0ah	; 0xAのとき次行と合わせて、
					; A + ('A'-'0'-A) + '0' = 'A'
_p4010:		add	al, '0'		; 0x0のとき、0 + '0' = '0'
		call	_putchar
		ret

; 8bit16進表示
; 入力
;   AL=数値
; 使用
;   なし
preg8:
		push	ax
		push	bx
		push	dx

		push	ax
		shr	al, 1
		shr	al, 1
		shr	al, 1
		shr	al, 1
		call	_preg4		; 上位4bit
		pop	ax
		call	_preg4		; 下位4bit

		pop	dx
		pop	bx
		pop	ax
		ret

; 16bit16進表示
; 入力
;   AX=数値
; 使用
;   なし
preg16:
		xchg	al, ah
		call	preg8		; 上位8bit
		xchg	al, ah
		call	preg8		; 下位8bit
		ret

; 文字列、数値、区切り文字のセット表示(private)
; 入力
;   DS:SI=文字列のアドレス
;   AX=数値
;   DL=区切り文字
; 使用
;   AX
_preg:		call	puts
		call	preg16
		mov	al, dl
		call	putc
		ret

; 全レジスタ16進表示
; 入力
;   なし
; 使用
;   なし
pregall:
		push	ax
		push	dx
		push	si
		push	ds

		push	ax
;		push	cx
		push	dx
;		push	bx
;		push	sp
;		push	bp
		push	si
;		push	di
;		push	ss
;		push	es
		push	ds
;		push	cs

		push	cs
		pop	ds

		mov	si, msg_cs
		mov	ax, cs		;	pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_ds
		pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_es
		mov	ax, es		;	pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_ss
		mov	ax, ss	;	pop	ax
		mov	dl, 0ah
		call	_preg

		mov	si, msg_di
		mov	ax, di	;	pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_si
		pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_bp
		mov	ax, bp	;	pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_sp
		mov	ax, sp	;	pop	ax
		mov	dl, 0ah
		call	_preg

		mov	si, msg_bx
		mov	ax, bx	;	pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_dx
		pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_cx
		mov	ax, cx	;	pop	ax
		mov	dl, ' '
		call	_preg

		mov	si, msg_ax
		pop	ax
		mov	dl, 0ah
		call	_preg

		pop	ds
		pop	si
		pop	dx
		pop	ax
		ret

msg_cs		db	'CS=', 0
msg_ds		db	'DS=', 0
msg_es		db	'ES=', 0
msg_ss		db	'SS=', 0
msg_ax		db	'AX=', 0
msg_bx		db	'BX=', 0
msg_cx		db	'CX=', 0
msg_dx		db	'DX=', 0
msg_si		db	'SI=', 0
msg_di		db	'DI=', 0
msg_bp		db	'BP=', 0
msg_sp		db	'SP=', 0
