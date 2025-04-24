#calc:
#	gcc add.c sub.c calc.c -o calc
#使用变量编写calc $@代表当前上述所有目标；$^代表当前上述所有依�?

#伪目�? .PHONY:clean  �? 被定义为伪目标后Makefile将不会判断目标是否存在或目标是否更新。如果没定义伪目标，然后当前文件下有一个clean文件，那么你make clean将无�?

#模式匹配�?1.使用通配�?%：表示所�?  �? %.o:%.c
#		  2.替换函数�?$(patsubst %.c %.o,$(wildcard ./*.c))
.PHONY:clean

OBJ = $(patsubst %.c,%.o,$(wildcard ./*.c))
TARGET = calc

$(TARGET):$(OBJ)
	$(CXX) $^ -o $@


%.o:%.c
	$(CXX) -c $^ -o $@

clean:
	del *.o calc.exe

show:
	echo $(CC)
	echo $(AS)
	echo $(CPP)
	echo $(RM)
