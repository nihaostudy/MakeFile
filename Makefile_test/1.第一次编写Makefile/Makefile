#calc:
#	gcc add.c sub.c calc.c -o calc


calc:add.o sub.o
	gcc add.o sub.o calc.c -o calc

add.o:add.c
	gcc -c add.c -o add.o

sub.o:sub.c
	gcc -c sub.c -o sub.o

