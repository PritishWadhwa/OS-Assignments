default:
	nasm -felf64 P1_asm.asm -o P1_asm.o
	gcc -c P1_c.c -o P1_c.o
	ld -e main P1_c.o P1_asm.o -o P1 
	./P1
object:
	nasm -felf64 P1_asm.asm -o P1_asm.o
	gcc -c P1_c.c -o P1_c.o
link:
	ld -e main P1_c.o P1_asm.o -o P1
run:
	./P1