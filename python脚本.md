# 设置参数

> scripty.py

```python
import argparse

# 输入参数
parser = argparse.ArgumentParser()
parser.add_argument("-f", "--source_file.c", help="generate a code_picture for a .c/.cc file", type=str, dest="source_file")
args = parser.parse_args()

source_file = args.source_file
```

shell使用方法：

```shell
python3 script.py -f 15-2CGIServer.cc
```



# 执行shell命令

```python
import os
os.system("ls -la")
```



# 获得shell的输出

```python
import os
find_str = "ls -la"
process = os.popen(find_str)        #shell输出保存在process中
source_file_path = process.read()   #读取输出内容
process.close()
```



