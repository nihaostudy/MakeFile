# Makefile

## 	一、相关知识点

### 	1. gcc

​	GCC全名为GUN Compiler Collection(GUN编译器套件)，属于一种编程语言编译器，初衷是为了GNU操作系统专门开发的一款编译器，gcc(GUN C Compiler)是GCC中的一款C语言编译器，类似的还有g++(GUN C++ Compiler)是GCC中的c++编译器。

![image-20250420111144480](C:\Users\abc18\AppData\Roaming\Typora\typora-user-images\image-20250420111144480.png)

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

### 3. Makefile编译动静态链接库

（1）概念

​	链接：如果一个函数包含太多语句时，这时候就需要子函数来归类这些语句，同样道理，一个源文件中包含了太多的函数时，就需要分多个源文件了，源文件会被分别编译，最后链接在一起。

![image-20250422110912702](C:\Users\abc18\AppData\Roaming\Typora\typora-user-images\image-20250422110912702.png)

​	当一个文件有太多源文件时，便不好理解，于是将一部分源文件预先编译成库文件，当需要使用其中文件时，只需要链接这个库文件就可以。可以将hello.cpp编译成静态库文件hello.lib。.lib文件是cpp文件编译而成的文件，它是任意个obj文件的集合，注意，这里仅仅是集合而已，不涉及到link，所以，在编译这种静态库工程时，你根本不会遇到链接错误。即使有错，错误也只会在使用这个lib的EXE或者DLL工程中暴露出来。 

​	动态链接库：是一种二进制文件，**Linux下后缀是.so，windows下后缀是.dll**。在编译时没有被编进目标程序中，而是在程序执行到相关函数时被调用。因此动态函数库所产生的可执行文件比较小。由于函数库没有被整合进你的程序，而是程序运行时动态的申请并调用，所以程序的运行环境中必须提供相应的库。动态函数库的改变并不影响你的程序，所以动态函数库的升级比较方便。（**运行时才加载**，**程序可以和库文件分离，可以分开发版，库文件可以被多处移植**）

​	静态链接库：名字一般**libxxx.a**，利用静态库编译成的文件一般比较大，因为整个函数库的所有数据都会被整合进目标代码，他的优点就显而易见了，即编译后的执行程序不需要外部的函数库支持，也就是不用部署了，运行时不用加载库文件，运行速度快，因为所有使用的函数都已经被编译进去了。当然这也会成为他的缺点，因为如果静态函数库改变了，那么你的程序必须重新编译。

举个例子：
你要远行，在路上走三天三夜。
动态库就相当于，你背了一袋粮食路上吃，饿的时候才拿出来吃。
静态库就相当于，你在出发前先吃饱，吃饱了在上路，不带粮食。



（2）动态链接库

```
add.c -> libadd.so
gcc -shared -fPIC add.c -o libadd.so //Linux下的编译动态库方法
gcc -shared -o libtest.dll add.o sub.o -Wl,--out-implib,libtest.dll.a 
//Windows下编译动态库方法，其中-Wl,XXX 告诉gcc把参数XXX传给链接器ld，--out-implib,libtest.dll.a指定库文件为libtest.dll.a
//libtest.dll：真正的动态库，运行时用（执行 .exe 时要它），libtest.dll.a：导入库，链接时用（编译 .exe 时需要这个）
gcc test.c -L. -ltest -o test.exe//当前文件下找到导入库libtest.dll.a编译
./test //运行时使用libtest.dll
[Linux]
┌──────────────┐       ┌────────────────────────┐
│ libxxx.so    │<──────│ main.c → 编译 → main   │
└──────────────┘       └────────────────────────┘
            ↑
        （运行时加载）

[Windows]
┌──────────────┐       ┌────────────────────────┐
│ libxxx.dll.a │──────▶│ main.c → 编译 → main.exe │
└──────────────┘       └────────────────────────┘
            │
┌──────────────┐
│ xxx.dll      │（必须存在于运行路径或系统 PATH）
└──────────────┘

```

```
为什么需要使用动态链接库？
// add.c
int add(int a, int b) {
    return a + b;
}

// sub.c
int sub(int a, int b) {
    return a - b;
}
// test.c
#include <stdio.h>
int add(int, int);
int sub(int, int);

int main() {
    printf("add = %d\n", add(3, 2));
    printf("sub = %d\n", sub(3, 2));
    return 0;
}
我写的动态链接add.c和sub.c，链接好直接给test使用。
若直接编译成一个test.exe文件也没错，但如果以后有十个程序、甚至一百个程序都使用了add()和sub()，那该怎么办？
场景一：不用动态库（静态方式或每次都编译）
你有 100 个项目都用了 add()、sub()：
每个 .exe 都把 add()、sub() 的代码包含进来了
最终生成的 .exe 都变大了
改 add() 的算法时，要重新编译 100 个程序！
🙅‍♂️ 这就像每个人出门都自己带一把剪刀、锤子，太浪费了。

场景二：使用动态库（DLL）
你写一次 add() 和 sub()，放到 libtest.dll：
只生成一个 DLL 文件（公共函数库）
所有程序在运行时共享这一个 DLL
如果要修改 add()，只改 DLL 就行，所有程序都会自动“升级”
✅ 这就像一家人共享一套工具：省空间、好维护！（3）
```

（3）静态链接库

```
gcc -c add.c sub.c  //编译生成.o文件
ar rcs libtest.a add.o sub.o //打包成静态库.a  r：把文件加进库，如果已存在就替换  c:创建库文件  s:建立符号索引表，方便 ld 查找函数符号
gcc test.c -L. -ltest -o test.exe //这个 -ltest 会链接 libtest.a，把 add() 和 sub() 的机器码打包进 test.exe 中。
//Linux和Windows一样
```

```
为什么要使用静态库？
小项目 / 独立发布程序	拿一个 .exe 就能跑，方便发给别人
追求性能	直接运行更快
[使用静态库时]
┌──────────────┐
│ libtest.a    │ ←  add.o, sub.o 打包
└────┬─────────┘
     │
┌────▼────────────────────┐
│ test.c → 编译 → test.exe│ ← 内含 add(), sub()
└────────────────────────┘
    ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
（函数代码已经拷贝到程序里）

[使用动态库时]
test.exe  ← 只留下接口
libtest.dll ← 才是函数实现
```

### 4. Makefile中通用部分用作头文件

​	Makefile中都是先展开所有变量。再调用指令

​	“**=**” 赋值，但是用最终值，就是不管变量调用写在赋值前还是赋值后，调用都是取最终值

​	Makefile中都是使用最终值

​	“**:=**” 赋值，但是只受当前行及之前行影响，不受后面代码影响

**Makefile中通用部分用作头文件使用示例：**

![image-20250423171238746](C:\Users\abc18\AppData\Roaming\Typora\typora-user-images\image-20250423171238746.png)****

```
include ../makefile  //.//上一个目录。使用上一个目录的makefile
```

