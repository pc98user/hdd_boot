all:
	nasm -f bin -o force386.com force386.asm
#	nasm -f bin -o force386.bin force386.asm
	nasm -f bin -o fdboot.bin fd_boot.asm
	nasm -f bin -o sasiboot.bin sasi_boot.asm
	nasm -f bin -o scsiboot.bin scsi_boot.asm
	nasm -f bin -o printsam.bin print_sample.asm

clean:
	rm -f *.bin *.com
