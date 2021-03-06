# 1 vi和vim

vi是Linux自带的编辑器，对文件的编辑是全程用键盘操作的，因此需要学会一些查看、复制、粘贴、剪切、删除等操作。

vim是vi的高级版本，有高亮显示、根据文件类型进行语法检测等功能。



# 2 vi的三种模式

- 一般模式：使用vi打开一个文件后，显示的就是一般模式
  - 查看文件
  - 使用指令对文件进行复制粘贴等操作
- 编辑模式：在一般模式下输入`i`进入编辑模式，编辑模式下就是输入代码，按下`esc`返回到一般模式
- 命令行模式：对文件整体进行操作，如保存/读取文件，使用`:命令`执行



# 3 常用指令

- `vi file1 file2`：进入 vi 编辑器，编辑多个文件
- `:q`：退出 vi 编辑器
  - 通常使用`:wq`保存并退出编辑器



## 3.1 命令行模式下的常用指令

- `:files`：查看 vi 打开的多个文件
  - `:n`：编辑上一个文件
  - `:N`：编辑下一个文件

- `:w`：写入并保存文件
  - `:w!`：若文件为只读，强制写入并保存文件



## 3.2 一般模式下的常用指令

- `:set nu`：显示行号



### 3.2.1 移动光标

- `nG`：将光标移动到第n行
- `[Home]`：将光标移动到这一行的首字符
- `[End]`：将光标移动到这一行的尾字符
- `n[Space]`：将当前光标移动到后n个字符



### 3.2.2 ==选择==

这个是在vim编辑器中特有的功能，非常方便，相当于鼠标的选择

- `v`：字符选择，会将光标经过的地方反白显示
- `y`：复制反白的内容
- `p`：在光标处粘贴反白的内容
- `d`：删除反白的地方



### 3.2.3 删除、复制与粘贴

- `dd`：删除光标所在的一整行
  - `ndd`：删除光标所在的后n行
- `yy`：复制光标所在的一整行
  - `nyy`：复制光标所在的后n行
- `p`：将复制的数据在光标下一行进行粘贴



### 3.2.4 ==两个常用操作==

- `.`：重复前一个操作
- `u`：复原前一个操作，相当于CTRL+Z



### 3.2.5 查找与替换

- `/字符`：向下查找字符，只查找一次
- `?字符`：向上查找字符，只查找一次
- `n`：重复上一次查找操作

**查找与n一起使用，可以重复找到关键字。**

-  `:n1,n2s/原字符/替换字符/g`：替换n1行到n2行中原字符
- `:n1,$s/原字符/替换字符/gc`：体会n1行到最后一行中原字符，并提示是否确认替换



# 4 使用VSCode的Vim插件

0、安装gcc：`sudo apt-get install gcc`；`sudo apt-get install gcc-multilib`

1、安装VSCode

2、安装Vim和C/C++插件：

- C/C++：编译环境（必装）
- C/C++ GUN Global
- C/C++ Snippets：快速生成代码段
- EPITECH C/C++ Headers：为C/C++文件添加头部(包括作者、创建和修改日期等),并为.h头文件添加防重复的宏
- Include Autocomplete：头文件自动补全



3、打开shell，使用如下命令

```shell
code *.cc #使用vscode打开/创建一个源文件
```



## 4.1 VSCode常用快捷键

- VSCode快速打开终端：CTRL + `
- 切分组：CTRL + \
- 切换到组：CTRL + 1、2、3...



## 4.2 Debug环境设置

- 1、打开一个项目文件夹
- 2、点击调试按钮，自动生成一个C/C++的`launch.json`
  - 这个文件保存在当前项目文件夹下的`.vscode/launch.json`

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "debug hello",  //debug名称
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceFolder}/hello",  //当前目录下生成的可执行文件
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "为 gdb 启用整齐打印",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ]
        }
    ]
}
```

- 调试前，需要添加-g编译选项，生成可执行文件
- 打断点，按F5进入调试模式