#Makefile自定义函数,不是真正的函数，本质是多行命令，相当于宏定义，自定义函数没有返回值
# $(1) $(2) 参数1和参数2,传参使用
#echo $(0) 是打印自己函数名称  
define my_func
	echo "Hello World!"
	echo $(1) $(2)        
endef

all:
	$(call my_func,abc,def)