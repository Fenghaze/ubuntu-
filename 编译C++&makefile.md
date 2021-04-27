# 1 源码、编译程序、可执行文件

源码：使用编程语言编写的纯本文文件（`.c`, `.cpp`, `.py`），人看得懂，机器看不懂

编译程序：使用**编译器**将源码**编译**成机器看得懂的==二进制文件==，编译过程中会生成**目标文件**（`.o`, `.obj`）

有时，程序中会调用其他的外部子程序或函数库的函数，这时候，就必须要在编译过程中将函数库加进去。

编译器的做法就是将程序代码和函数库链接（link）起来，生成正确的可执行文件。

可执行文件：**在Linux中，可执行文件都是二进制文件**



# 2 Linux下编译C++源程序

## 2.1 编译

在Linux中，编译C的编译器是`gcc`，编译C++的编译器是`g++`

- `g++ *.cpp`：编译一个或多个源文件，会生成一个`a.out`可执行的二进制文件，而不是`.o`文件

  

- `g++ -c *.cpp`：编译一个或多个源文件，生成一个与源程序同名的`*.o`目标文件，不可执行

- `g++ *.o -o test `：链接一个或多个目标文件`*.o`生成一个名为`test`的二进制可执行文件



- `g++ -c *.cc -o test`：==一步到位==，先`-c`编译一个或多个源文件，再`-o`生成可执行文件，但不会生成`.o`目标文件



==使用`-o`生成目标文件的原因:==

当有多个源文件时，且多个文件有相互调用，此时就无法直接进行编译，需要借助生成的目标文件`*.o`，将目标文件**链接**在一起，最后生成一个可执行文件



### 编译预处理

在编译时，还有一个**编译预处理**过程，这个过程时导入源代码中引用的头文件、宏定义等

`g++ -E *.cpp`：进行编译预处理，预处理结束后停止编译

预处理过的文件的 GCC 后缀为`.ii`，它可以通过 `-o` 选项来生成：`g++ -E *.cpp -o *.ii`



## ==编译选项==

gcc source_file.c：无编译选项，生成名为a.out的可执行文件

gcc (-E/S/c/..) source_file.c -o output_filename：-o生成可执行文件名，可以配合下面的编译选项使用

==gcc -c source_file.c==：只执行到编译，输出目标文件`.o`

gcc -g source_file.c ：生成供调试用的可执行文件，可以在gdb中运行

gcc -E source_file.c：只执行到预编译。直接输出预编译结果。

gcc -S source_file.c ：只执行到源代码到汇编代码的转换，输出汇编代码。

gcc -O source_file.c：编译器对代码进行自动优化编译，输出效率更高的可执行文件。-O 后面还可以跟上数字指定优化级别，如：gcc -O2 source_file.c
数字越大，越加优化。但是通常情况下，自动的东西都不是太聪明，太大的优化级别可能会使生成的文件产生一系列的bug。一般可选择2；3会有一定风险

gcc -Wall source_file.c：在编译中开启一些额外的警告（warning）信息。-Wall，将所有的警告信息全开

gcc source_file.c -L /path/to/lib -lxxx -I /path/to/include
-l, 指定所使用到的函数库
-L，指定函数库所在的文件夹
==-I, 指定头文件所在的文件夹==



#  3 makefile和make

## 3.1 基本使用

当有多个文件要进行编译时，如果使用命令行则会比较繁琐，而且如果经常要修改源文件，又要从头敲命令行进行编译。

makefile这个文件保存的就是编译时要使用的命令行，创建完毕后，使用`make`命令就能完成编译。

makefile基本语法：

```shell
项目名：*.o（依赖的目标文件）
	g++ *.o -o 项目名

*.o（生成的目标文件）：*.c（依赖的源文件）
	g++ *.c -o *.o

clean: # 删除原来生成的目标文件和可执行文件
	rm -rf *.o 项目名
```

- `make clean`：编译前先删除原来的文件
- `make 可执行文件名`：编译并生成可执行文件
- `make clean 可执行文件名`：一步到位，先删除再编译



**例子**：

```shell
# 有3个文件，main.cpp, haha.cpp, value.cpp
g++ -c main.cc haha.cc value.cc -o test
# 每次修改其中以个源文件，都要重新输入这个命令进行编译
```

使用vim创建makefile

```shell
test: main.o haha.o value.o
	g++ main.o haha.o value.o -o test 
clean: # 删除原来生成的目标文件和可执行文件
	rm -rf main.o haha.o value.o test
```

或使用shell的语法

```shell
OBJS=main.o haha.o value.o
CFLAGS+=-c -g -Wall				# 编译选项

test: ${OBJS}
	g++ ${OBJS} -o test

main.o:main.cc
	g++ main.c ${CFLAGS} -o main.o
	
haha.o:haha.cc
	g++ haha.cc ${CFLAGS} -o haha.o
	
value.o:value.cc
	g++ value.cc ${CFLAGS} -o value.o

clean:
	rm -rf ${OBJS} test
```

### ==更简化的版本==

```shell
OBJS=main.o haha.o value.o
CC=g++
CFLAGS+=-c -g -Wall				# 编译选项

test: ${OBJS}
	${CC} $^ -o $@				# $^表示当前要依赖的文件 ${OBJS}；$@表示当前要生成的文件 test

%.o:%.cc						# %表示找到所有源文件，生成所有与之对应的目标文件
	${CC} $^ ${CFLAGS} -o $@

clean:
	rm -rf ${OBJS} test
```

### ==编译带头文件的项目==

假设有：`main.c`、`func1.c`、`func1.h`；其中`main.c`包含`func1.h`头文件

```shell
CC=gcc
CFLAGS+=-c -g -Wall

main1: func1.o main1.c	# main1.c 中引入了头文件，无法单独编译生成 main1.o，因此需要最后一起编译
	$(CC) $^ -o $@	#生成可执行文件main1

%.o: %.c
	$(CC) $(CFLAGS) $^ -o $@	#生成.o文件

clean:
	rm -rf *.o main1
```

#### 实例

```shell
/home/src/
    |--cpp1.cc
    |--cpp2.cc
    |---main.cc
/home/include/
    |---cpp1.h
    |---cpp2.h
/home/build/
	|---build.sh
```

> cpp1.h

```c++
#include<iostream>
using namespace std;
void print1();
```

> cpp1.cc

```c++
#include"cpp1.h"
void print1()
{
	cout<<"this is cpp1"<<endl;
}
```

> cpp2.h

```c++
#include<iostream>
using namespace std;
void print2();
```

> cpp2.cc

```c++
#include"cpp1.h"
void print1()
{
	cout<<"this is cpp1"<<endl;
}
```

> main.cc

```c++
#include<iostream>
#include"cpp1.h"
#include"cpp2.h"
using namespace std;
int main()
{
    print1();
	print2();
    return 0;
}
```

**用指令编译：**==就是分别把除了`main.cc`以外的源文件都编译成目标文件，然后再和`main.cc`进行链接==

> build.sh

```shell
cd ..
cd src
g++ -c cpp1.cc cpp2.cc
g++ main.cc cpp1.o cpp2.o -o output -I /home/include 
rm *.o
./output
```

运行：

```shell
sh build.sh
```



> makefile

```shell
OBJS=cpp1.o cpp2.o
CC=g++
CFLAGS+=-c -g -Wall

output: $(OBJS) main.cc
	$(CC) $^ -o $@

%.o:%.cc
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJS) output
```



**总结：** 无论我们采用哪种方式编译，总需要告诉编译器我们要编译哪些源文件`.cc`，以及这些`.cc`用到的头文件`.h`（路径）在哪里。这些`.cc`用到的第三方库是什么（库文件名字），库在哪里（库路径），库给我们的接口在哪里（库头头文件路径，我们在写`.cc`时通过include头文件，用接口调用相应的库实现）



## 3.1 进阶

### 3.1.0 当前目录下的所有文件使用统一编译选项

创建makefile文件

加入`-fopenmp`选项

```makefile
CFLAGS+=-pthread -g -Wall -fopenmp
LDFLAGS+=-pthread 
```

### 3.1.1 指定文件目录

makefile默认在当前目录下查找源文件，但是大多数情况下，源文件是分类在不同文件夹下的，因此需要在makefile中指定文件搜索的目录

使用`VPATH`变量就可以完成这个功能，如果定义了这个变量，那么make 就会在当前目录找不到的情况下，到所指定的目录中去找寻文件了

```shell
VPATH = src:相对路径1:相对路径2:...:相对路径n		# 使用:冒号将路径分隔开
```



### 3.1.2 生成多个可执行文件

在同一文件夹下，要生成两个或两个以上的可执行文件

添加一个`all：`

如：func1.c, func1.h, main1.c；func2.c, func2.h, main2.c

```shell
CC=gcc
CFLAGS+=-c -g -Wall

all: main1 main2		# 生成所有的项目文件

main1: func1.o main1.c
	$(CC) $^ -o $@

main2: func2.o main2.c
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -rf *.o main1 main
```



## 3.2 一些语法

### @echo：打印

```
src := 12345
@echo $(src)
在终端打印 12345
```



### foreach：循环

> 语法：$(foreach , , )
>
> 功能：foreach是用来做循环用的，类似于for 语句

例：

```
names := a b c d
files := $(foreach n,$(names),$(n).o)
$(name)中的单词会被挨个取出，并存到变量“n”中，“$(n).o”每次根据“$(n)”计算出一个值，这些值以空格分隔，最后作为foreach函数的返回
$(files)的值是“a.o b.o c.o d.o”
```



### ==wildcard：搜索目录下的文件==

> 语法：$(wildcard \*.c path/\*.c)
>
> 功能：得到指定目录下所有的C语言源程序文件名的方法，不用手工一个一个指定需要编译的.c文件

```
指定编译当前目录下所有.c文件
SRC = $(wildcard *.c) 

如果还有子目录，比如子目录为inc，则再增加一个wildcard函数：
SRC = $(wildcard *.c) $(wildcard inc/*.c)
SRC = $(wildcard *.c inc/*.c)

也可以指定汇编源程序： 
ASRC = $(wildcard *.S)
```



### addprefix：添加前缀

> 语法：$(addprefix , )  
>
> 功能：加前缀函数，把前缀加到中的每个单词前
>
> 返回：返回加过前缀的文件名序列

```
$(addprefix src/,foo bar)
返回值是“src/foo src/bar”
```



### notdir:去除路径

> 语法：$(notdir src)
>
> 功能：去除前缀路径，保留最后的路径

```
src := a.c b.c ./sub/sa.c ./sub/sb.c
$(notdir $(src))
返回值是 a.c b.c sa.c sb.c
```



### ==patsubst ：替换通配符==

> 语法：$(patsubst <pattern>, <replacement>, <text>)
>
> 功能：查找<text>中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式<pattern>，如果匹配的话，则以<replacement>替换。这里，<pattern>可以包括通配符==“%”，表示任意长度的字串==。如果<replacement>中也包含“%”，那么，<replacement>中的这个“%”将是<pattern>中的那个“%”所代表的字串。（可以用“\”来转义，以“\%”来表示真实含义的“%”字符）
>
> 一般与wildcard一起使用，先找到所有源文件，然后替换.c生成.o的文件

```
dir := a.c b.c sa.c sb.c
obj=$(patsubst %.c, %.o, $(dir))
返回值 a.o b.o sa.o sb.o
```



