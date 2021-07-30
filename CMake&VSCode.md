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

> 执行cmake

```shell
cmake .
make
```



> 分文件编写
>
> ```shell
> - bin				# 生成的目标文件存放在此处
> - build				# 生成的cmake文件存放在此处
> - CMakeLists.txt
> - include			# 存放头文件
> 	- a.h
> 	- b.h
> - src				# 存放源文件
> 	- main.cpp
> 	- a.cpp
> 	- b.cpp
> ```

```cmake
cmake_minimum_required(VERSION 3.10)

project (main)

# SRC_LIST源文件目录为 src
aux_source_directory (src SRC_LIST)

# 依赖的头文件目录为 include
include_directories (include)

# 生成目标文件 main
add_executable (main ${SRC_LIST})

# -pthread 编译选项
find_package(Threads)
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})

# -Wall -g 编译选项
add_definitions("-Wall -g")

# 目标文件输出目录为 bin
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
```

> 执行cmake

```shell
cd build
cmake ..
make
```



> 多个目录下的源文件：每个目录下创建CMakeLists.txt
>
> ```cmake
> - CMakeLists.txt		#顶层cmakelist
> - main.cpp
> - hello			
> 	- CMakeLists.txt
> 	- hello.cpp
> 	- hello.h
> - world
> 	- CMakeLists.txt
> 	- world.cpp
> 	- world.h
> ```

> 顶层CMakeLists.txt	

```cmake
cmake_minimum_required(VERSION 2.8)
project(helloworld)

# Add the source in project root directory
aux_source_directory(. DIRSRCS)
# Add header file include directories
include_directories(./ ./hello ./world)
# Add block directories
add_subdirectory(hello)
add_subdirectory(world)
# Target
add_executable(helloworld ${DIRSRCS})
target_link_libraries(helloworld hello world)
```

> hello/CMakeLists.txt

```cmaek
aux_source_directory(. DIR_HELLO_SRCS)
add_library(hello ${DIR_HELLO_SRCS})
```

> world/CMakeLists.txt

```cmake
aux_source_directory(. DIR_WORLD_SRCS)
add_library(world ${DIR_WORLD_SRCS})
```



> 多个目录下的源文件
>
> ```cmake
> - CMakeLists.txt		#顶层cmakelist
> - main.cpp
> - hello			
> 	- hello.cpp
> 	- hello.h
> - world
> 	- world.cpp
> 	- world.h
> ```

```cmake
cmake_minimum_required(VERSION 2.8.3)
project (helloworld)
# Add header file include directories
include_directories(./hello ./world)
# Add block directories
set(HELLO_SRC hello/hello.cpp)
set(WORLD_SRC world/world.cpp)
# Target
add_executable(helloworld main.cpp ${HELLO_SRC} ${WORLD_SRC})
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

