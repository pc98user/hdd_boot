;===========================================================
; printlib.inc
;
; 文字列表示ライブラリ
;===========================================================
;cpu		8086
;bits		16

SCREEN_WIDTH	equ	80
SCREEN_HEIGHT	equ	25

; 改行する(private)
; 入力
;   なし
; 使用
;   AX
_newline:
		xor	ax, ax		; CR
		mov	[cs:col], ax
		mov	ax, [cs:line]

		inc	ax		; LF
		cmp	ax, SCREEN_HEIGHT
		jne	_nl010
		xor	ax, ax		; 1行目に戻す
_nl010:		mov	[cs:line], ax
		ret

; 1文字表示(private)
; 入力
;   AL=文字
; 使用
;   AX,BX,DX
_putchar:
		push	ds

		push	ax
		mov	ax, [cs:line]
		mov	dl, SCREEN_WIDTH	; 行位置*80
		mul	dl		; axは255を超えないのでal*dlでよい
		add	ax,  [cs:col]		; +桁位置
		shl	ax, 1			; アドレス*2
		mov	bx, ax
		mov	ax, 0a000h		; TEXT VRAM
		mov	ds, ax
		pop	ax

		mov	[bx], al
		mov	byte [bx+1], 00h

		pop	ds

		mov	ax, [cs:col]
		inc	ax			; 1桁進める
		cmp	ax, SCREEN_WIDTH
		je	_pc010			; 改行へ
		mov	[cs:col], ax
		ret
_pc010:		call	_newline
		ret

; 1文字表示
; 入力
;   AL=文字、改行コード
; 使用
;   なし
putc:
		push	ax
		push	bx
		push	dx

		cmp	al, 0ah
		je	ptc010		; 改行のとき
		call	_putchar
		jmp	ptc090
ptc010:		call	_newline
ptc090:
		pop	dx
		pop	bx
		pop	ax
		ret

; 文字列表示
; 入力
;   DS:SI=文字列のアドレス
; 使用
;   SI
puts:
		push	ax
		push	bx
		push	dx

pts010:		lodsb			; 1文字読み込み
		cmp	al, 00h
		je	pts090		; EOLのとき
		cmp	al, 0ah
		je	pts020		; 改行ののとき
		call	_putchar
		jmp	pts010
pts020:		call	_newline
		jmp	pts010
pts090:
		pop	dx
		pop	bx
		pop	ax
		ret

col		dw	0 ; 桁位置
line		dw	0 ; 行位置
