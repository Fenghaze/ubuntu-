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
	$(CC) $^ -o $@

%.o: %.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -rf *.o main1
```





## 3.1 进阶

### 3.1.0 当前目录下的所有文件使用统一编译选项

加入`-fopenmp`选项

```makefile
CFLAGS+=-pthread -g -Wall -fopenmp
LDFLAGS+=-pthread 
```



## 3.1.1 指定文件目录

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

