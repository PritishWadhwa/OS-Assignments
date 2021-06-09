default:
	gcc hello.c -o hello
	./hello
preprocess:
	gcc -E hello.c -o hello.i
compile:
	gcc -S hello.i -o hello.s
assemble:
	gcc -c hello.s -o hello.o
link:
	gcc hello.o -o hello
run:
	./hello