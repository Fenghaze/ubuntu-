# 1 shell 基础

## 1.1 硬件、内核、shell的关系

内核：管理计算机硬件和进行资源分配的一组程序，向外部提供接口，开发人员可以根据这些接口编写软件



shell：是一个软件，功能是为用户提供一个内核接口，使得用户通过shell来调用内核，让内核完成硬件任务。



狭义的shell指的是命令行软件，如Linux使用的 bash shell。

==用户在shell终端输入命令行，shell对命令行进行语法解析，随后调用内核，内核再执行相关操作。==

在此过程中，shell只充当了**信息传递**、**信息解析**的角色。



广义的shell指的是图形界面的应用软件，这些软件也能操作各种应用程序来调用内核进行工作



简单来说，用户只有通过shell才能调用内核进行工作。



## 1.2 变量

特殊变量：

- `$`：本身也是一个变量，变量内容是当前shell的PID
- `?`：变量内容是上个执行命令的回传码，用于检查命令是否执行成功



### 1.2.1 变量设置与读取

- 一般变量设置方式：`变量名=变量内容`，等号两边不能有空格

- 添加`$`获得变量内容：`$变量名`或`${变量名}`

- 导出变量：`export 变量名`
- 取消变量设置：`unset 变量名`

- 显示变量：`echo $变量名`



> 例子中，变量内容用了双引号，并且在引号内使用`$name`获取了`name`的变量内容。

```shell
name=Mary
msg="$name is running"  # Mary is running
```



> 例子中，使用`"$变量名" 变量内容`可以追加内容

```shell
word=123
word="$word"456 # 123456
```



### 1.2.2 变量键盘读取 read

`read [-p "msg" -t n] 变量名`：在shell可以进行键盘交互功能，用户输入变量内容为变量赋值。

- -p：输入提示
- -t：可以设置输入等待时间为n秒，超过时间无法输入



### 1.2.3 声明变量类型 declare

`declare [-aixr] 变量名`：默认为字符型

- -a：数组类型
- -i：整型
- -x：设置为环境变量
- -r：设置为只读，不可更改不可重设



### 1.2.4 变量删除

在使用`echo`时，配合通配符进行变量的删除：

- 从前往后删除最短的字符串，关键符号`#`
  - `##`表示删除匹配到的最长字符串
- 从后往前删除，关键符号`%`
  - `%%`表示删除匹配到最长字符串

```shell
path="/usr/kerberos/sbin:/usr/kerberos/bin:/usr/bin:/root/bin"
echo ${path#/*/kerberos/bin:}
/usr/bin:/root/bin
# 从前往后删除匹配到的最短字符串，从 / 开始，* 表示中间任意字符串， 到 /kerberos/bin: 结束

echo ${path##/*:}
/root/bin
# 从前往后删除匹配到的最长字符串，从 / 开始，* 表示中间任意字符串，到 : 结束

# % 同理
```



### 1.2.5 变量替换

`${旧变量名-新变量内容}`：若旧变量不存在，则赋值新变量内容；否则，无法替换

`${旧变量名:-新变量内容}`：若旧变量不存在或设置为空，则赋值新变量内容



## 1.3 数据流重定向

含义：就是将某个命令执行后应该要出现在屏幕上的内容传输到文件中。（将屏幕的内容保存为文本）



## 1.4 管道 pipe

含义：就是将某个命令执行后的内容进行**过滤**，再在屏幕上展示。



# 2 shell script 快速开始

shell script是利用 shell 的功能所写的一个程序，这个程序是纯文本文件。

就是将一些 shell 的语法和命令（含外部命令）写在里面，搭配正则表达式、管道命令与数据流重定向等功能，以达到所想要的处理目的。

在shell script里面，可以使用数组、循环、条件逻辑判断等功能，shell script执行的顺序是：**从上至下，从左至右**。

## 2.1 书写规范

在每个script的文件头处记录以下信息：

- 声明使用的 shell 的名称

- 功能
- 历史纪录
- 对于特殊的命令，使用**绝对路径**的方式进行
- 执行时需要的环境变量预先声明与设置

程序编写完成后，在shell输入`sh 文件名.sh`执行。



## 2.2 应用

- 自动化管理服务器
- 追踪与管理系统的重要工作
- 简单入侵检测功能
- 连续命令单一化
- 简单的数据处理



## 2.3 Hello World！

> Hello World

```shell
#!/bin/bash
# Program:
# 	Hello World!
#History:
#	2020-06-05 zhl First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

echo "Hello World! \a \n"

exit 0
```

`#`：注释

PATH：是预先声明 shell 中的环境变量，当用到外部命令时，从PATH中按顺序查找外部命令，然后执行。

export PATH：导出这个变量后，其他子进程就可以使用

exit 0 ：告知执行结束，相当于 return 0



# 3 简单范例

## 3.1 交互式 script

用户通过键盘输入来给变量赋值

```shell
#!/bin/bash
# Program:
# 	User inputs his first name and last name. Program shows his full name.
#History: 
# 	2020-06-05 zhl First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

read -p "Your first name:" firstname
read -p "Your last name:" lastname
echo "\n Your full name: $firstname $lastname"

exit 0
```



## 3.2 自动更新日期信息

《鸟哥私房菜》 P377