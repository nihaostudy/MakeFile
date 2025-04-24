#Makefile中只有一个循环 foreach  $(foreach var,list,text) 
#var 是一个临时变量，它只在 foreach 函数的上下文中有效。foreach 函数执行完毕后，var 变量将不再起作用。

#list 可以是一个表达式，它会被展开并用于循环。

#text 中通常会使用 var 变量来枚举 list 中的元素。

#foreach 函数的返回值是所有迭代中 text 表达式返回的字符串，这些字符串之间用空格分隔。
#假设我们有一个名为 names 的列表，包含了 a、b、c 和 d 四个元素，我们想要为每个元素生成一个以 .o 结尾的文件名。我们可以使用 foreach 函数来实现这一点：

names := a b c d
files := $(foreach n,$(names),$(n).o)