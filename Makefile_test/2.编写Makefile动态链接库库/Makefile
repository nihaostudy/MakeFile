//动态编译
cc = gcc
CFLAGS = -Wall

LIB_NAME = libtest

src = add.c sub.c
obj = add.o sub.o

all : $(LIB_NAME).dll test.exe

$(LIB_NAME).dll : $(obj)
	gcc -shared -o $(LIB_NAME).dll $(obj) $(CFLAGS),--out-implib=$(LIB_NAME).dll.a

test.exe : test.c $(LIB_NAME).dll.a
	gcc test.c -L. -ltest -o test.exe

clean:
	del *.o *.dll *.dll.a *.exe 




