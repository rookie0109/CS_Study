# CMake
## 常见语法
```cmake

# 声明最低版本
camke_minimum_required(VERSION 2.8)

# 声明cmake 工程
project(HelloSLAM)

# 设置要编译的C++版本
set(CMAKE_CXX_FLAGS "-std=c++11")

# 指定编译过程中要包含的头文件目录
include_directories([AFTER|BEFORE] [SYSTEM] directory1 [directory2 ...])
# 常见 include_directories(/path/to/include1 /path/to/include2)

# 添加库
add_library(targetName [SHARED | STATIC | MODULE] source1 [source2 ...])  # MODULE模块库

# 添加可执行程序
add_executable(exe_name main.cpp)

# 将库文件链接到可执行程序上，或者链接一个库到另一个库上
target_link_libraries(useHello hello_shared)
target_link_libraries(target library1 [library2 ...])


```