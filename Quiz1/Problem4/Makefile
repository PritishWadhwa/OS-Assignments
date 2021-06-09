default:
	nasm -felf32 P4_1.asm -o P4_1.o
	gcc -m32 P4_1.o P4_1.c -o P4_1
	./P4_1
32bitMode:
	nasm -felf32 P4_1.asm -o P4_1.o
	gcc -m32 P4_1.o P4_1.c -o P4_1
	./P4_1
64bitMode:
	nasm -felf64 P4_2.asm -o P4_2.o
	gcc P4_2.o P4_2.c -o P4_2
	./P4_2