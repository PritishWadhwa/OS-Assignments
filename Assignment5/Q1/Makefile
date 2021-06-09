compile1:
	nasm -f bin printHello_2019440.asm -o printHello_2019440.bin

run1: compile1
	qemu-system-x86_64 printHello_2019440.bin

compile2:
	nasm -f bin printCR0_2019440.asm -o printCR0_2019440.bin

run2: compile2
	qemu-system-x86_64 printCR0_2019440.bin