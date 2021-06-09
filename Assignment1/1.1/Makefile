default:
	@gcc a1_1.c -o a1_1
	@./a1_1
preprocess:
	@gcc -E a1_1.c -o a1_1.i
compile:
	@gcc -S a1_1.i -o a1_1.s
assemble:
	@gcc -c a1_1.s -o a1_1.o
link:
	@gcc a1_1.o -o a1_1
run:
	@./a1_1