A = 1234

RS1 :=
RS2 :=

#ifeq 与条件之间要有空格，ifeq不可以用条件,没有else if的用法 ，要用得嵌套
ifeq ($(A),123)
	RS1 := xulong
else
	ifeq ($(A),1234)
		RS2 := xulong
	else
		RS1 := dudan
	endif
endif


all:
	echo $(RS1)
	echo $(RS2)