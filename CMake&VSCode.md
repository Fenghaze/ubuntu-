# CMake快速使用

## 创建`CMakeLists.txt`文件

> 项目结构目录：所有文件放在同一根目录下
>
> ```
> -http
> --| 15-6WebServer.cpp
> --| CMakeLists.txt
> --| http.cpp
> --| http.h
> --| locker.h
> --| threadpool.h
> ```

```cmake
#cmake的版本要求
cmake_minimum_required(VERSION 3.10)

#工程的名称
project(httpServer)

#生成可执行文件 后面是依赖的源文件
add_executable(server 15-6WebServer.cpp http.cpp)

#添加pthread编译选项
find_package(Threads)
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})
```



## 执行 cmake

```shell
cmake .
make
```



# VSCode安装CMake相关工具

- 安装CMake
- 安装CMake Tools



# VSCode执行cmake

- 右键选中`CMakeLists.txt`文件，选择配置所有项目（Configure All Project）生成一个`build`文件夹（或者点击底端栏的build）

- 点击底端栏的run即可运行生成的可执行文件



# VSCode调试

- 点击左侧栏的运行和调试的爬虫按钮，生成`launch.json`配置文件

- 修改`program`参数：指定为`build/生成的可执行文件`

```json
"program": "${workspaceFolder}/build/server"
```

- 重新执行cmake
- 打断点进行调试

