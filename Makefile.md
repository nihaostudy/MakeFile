# Makefile

## 	一、相关知识点

### 	1. gcc

​	GCC全名为GUN Compiler Collection(GUN编译器套件)，属于一种编程语言编译器，初衷是为了GNU操作系统专门开发的一款编译器，gcc(GUN C Compiler)是GCC中的一款C语言编译器，类似的还有g++(GUN C++ Compiler)是GCC中的c++编译器。

```
		gcc -o :指定编译生成的文件名
		gcc -E :执行预处理操作，即生成*.i文件，文本替换：宏定义+条件预处理+其他预处理等
				//预处理阶段不会检查语法错误
		gcc -S :执行编译阶段，将*.i文件转化为汇编代码*.s文件gcc -S Demo.i -o Demo.s
				//编译阶段会检查语法错误
		gcc -c ：执行汇编阶段，将*.s文件中的汇编源码转化为机器能执行的二进制机器码：*.s->*.o
		gcc *.o -o *.exe :链接阶段，生成可执行文件
```

### 	2. make

​	make工具可以看成一个智能的批量处理工具，本身没有编译和链接功能，通过调用**makefile文件**中用户指定的命令来进行编译和链接的，也就是makefile的规则。

### 	3. cmake

​	简单工程的makefile可以人工手写，但是面对复杂工程，手写makefile也是非常麻烦的，如果换了个平台makefile又要重新修改，这时候就出现了下面的Cmake这个工具。跨平台编译工具，使用cmake去生成Makefile也得去写一个规则CMakeLists.txt文件。

## 	二、什么是Makefile?

​	一个工程中的源文件不计其数，按照类型、功能、模块分别放在若干目录中，Makefile便可以简单的认为是一个工程文件的编译规则，描述了整个工程的编译和链接等规则，哪些文件需要先编译，哪些需要后编译以及哪些需要重新编译等操作，使项目编译变得自动化。

​	Makefile是make命令所读取的配置文件，包含了构建项目的规则。其主要作用是检查项目文件之间的依赖关系，自动执行必要的命令，更新目标文件，一般来说主要包括三部分：目标(target)、依赖(dependencies)和命令(commands)。

## 三、Makefile使用

### 1. Makefile的工作原理

​	make会根据Makefile的规则，依次检查目标文件的时间戳和依赖文件的时间戳。如果依赖文件的时间戳比目标文件的时间戳新，或者目标文件不存在，make会执行对应命令来生成或更新目标文件，make会递归检查依赖关系，直至所有目标文件都更新完成。

### 2. Makefile的语法规则

​	（1）Makefile 的基本语法由规则组成，基本格式如下：

```
target:dependencies
	commands
target：目标文件，可以是一个目标文件也可以是一个动作名称
dependencies：目标文件所依赖的文件或其他目标
commands：构建目标的命令，必须使用tab键开始
```

​	（2）Makefile变量的使用

```
1. 基本变量使用
变量名 = 变量
target:dependencies
	$(变量名) 
2. 常用内置变量
CC ： C编译器的名称，默认就是C编译器

$@ : 表示目标文件
$^ : 表示所有依赖文件
$< : 表示第一个依赖文件
```

​	（3）伪目标

​	所谓的伪目标可以这样来理解，它并不会创建目标文件，只是想去执行这个目标下面的命令。伪目标的存在可以帮助我们找到命令并执行。使用伪目标有两点原因：

- 避免我们的 Makefile 中定义的只执行的命令的目标和工作目录下的实际文件出现名字冲突。

- 提高执行 make 时的效率，特别是对于一个大型的工程来说，提高编译的效率也是我们所必需的。

  ```
  clean:
  	rm -rf *.o test
  规则中 rm 命令不是创建文件 clean 的命令，而是执行删除任务，删除当前目录下的所有的 .o 结尾和文件名为 test 的文件。当工作目录下不存在以 clean 命令的文件时，在 shell 中输入 make clean 命令，命令 rm -rf *.o test 总会被执行 ，这也是我们期望的结果。 如果当前目录下存在文件名为  clean 的文件时情况就会不一样了，当我们在 shell 中执行命令 make clean，由于这个规则没有依赖文件，所以目标被认为是最新的而不去执行规则所定义的命令。因此命令 rm 将不会被执行。为了解决这个问题，删除 clean 文件或者是在 Makefile 中将目标 clean 声明为伪目标。将一个目标声明称伪目标的方法是将它作为特殊的目标 .PHONY 的依赖，如下：
  .PHONY:clean
  这样 clean 就被声明成一个伪目标，无论当前目录下是否存在 clean 这个文件，当我们执行 make clean 后 rm 都会被执行。而且当一个目标被声明为伪目标之后，make 在执行此规则时不会去试图去查找隐含的关系去创建它。这样同样提高了 make 的执行效率，同时也不用担心目标和文件名重名而使我们的编译失败。在书写伪目标的时候，需要声明目标是一个伪目标，之后才是伪目标的规则定义。目标 "clean" 的完整书写格式如下：
  .PHONY:clean
  clean:
  	rm -rf *.o test
  ```

  （4）Makefile编写方式

  有四个文件和一个主文件：a.c、b.c、c.c、d.c和mian.c

  ```
  1.直接编译（不推荐，每一次更新子程序就所有都得更新）
  cpp:a.c b.c c.c d.c main.c
  	gcc a.c b.c c.c d.c main.c -o cpp
  2.编译加链接
  cpp:a.o b.o c.o d.o main.o
  	gcc b.o c.o d.o main.o -o cpp
  a.o:a.c
  	gcc -c a.c -o a.o
  b.o:b.c
  	gcc -c b.c -o b.o
  c.o:c.c
  	gcc -c c.c -o c.o
  d.o:d.c
  	gcc -c d.c -o d.o
  main.o:main.c
  	gcc -c main.c -o main.o
  3. 模式匹配
  src=add.o div.o multi.o sub.o main.o
  target=app
  $(target):$(src)
  	$(CC) $^ -o $@
  %.o:%.c
  	$(CC) -c $< -o $@ 
  ```


