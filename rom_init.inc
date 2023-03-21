;===========================================================
; BIOS ROMを初期化する
;===========================================================
;cpu		8086
;bits		16

; BIOS ROMを初期化する
; 入力
;   romsegs
; 使用
;   不定
rom_init:
		mov	bp, romsegs
rmi_loop:
		push	cs
		pop	ds

		; エントリ読み出し
		mov	bx, [bp]	; AX:BX
		mov	ax, [bp+2]
		cmp	ax, 0
		je	rmi_end		; 0で終わり

		mov	es, ax		; ES <- AX

		; アドレス表示
		mov	si, msg_romaddr
		call	puts
		call	preg16
		mov	al, ':'
		call	putc
		mov	ax, bx
		call	preg16

		; ROMの存在確認
		cmp	byte [es:bx+0009h], 55h
		jne	rmi_notexist
		cmp	byte [es:bx+000ah], 0AAh
		jne	rmi_notexist

		; 初期化中
		mov	si, msg_initialize
		call	puts
		push	bp
		call	far [bp]	; ROM呼び出し
		pop	bp

		; 完了
		mov	si, msg_done
		call	puts

		jmp	rmi_done

rmi_notexist:
		; 存在しない
		mov	si, msg_notexist
		call	puts
rmi_done:
		add	bp, 4
		jmp	rmi_loop	; 次のエントリへ

rmi_end:
		ret

;romsegs	dw	0000h, 0d400h
;		dw	0000h, 0dc00h
;		dw	0000h, 0d700h
;		dw	0, 0

msg_romaddr	db	"ROM address ", 0
msg_notexist	db	" - not exist.", 0ah, 0
msg_initialize	db	" - initializing... ", 0
msg_done	db	"done.", 0ah, 0
