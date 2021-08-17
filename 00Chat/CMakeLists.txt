# CMake 最低版本号要求: 指定运行此配置文件所需的 CMake 的最低版本
cmake_minimum_required (VERSION 2.8)

# 项目信息: 该命令表示项目的名称是 Chat
project (Chat)
#       (1)  (2)                (3)          (4)            (5)        (6)
#g++ -o main -g -std=c++11 main.cpp xxx.cpp -I/usr/include -L/usr/lib -Imuduo_net -Imuduo_base -Ipthread

# (1')设置cmake的全局变量 设定输出文件的路径
# EXECUTABLE_OUTPUT_PATH 代表二进制可执行文件的输出位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# (4) 添加头文件的搜索路径，相当于makefile里面的-I
Include_directories(${PROJECT_SOURCE_DIR}/include)
Include_directories(${PROJECT_SOURCE_DIR}/thridparty)
Include_directories(${PROJECT_SOURCE_DIR}/include/server)
Include_directories(${PROJECT_SOURCE_DIR}/include/server/db)


# (5) 添加库文件的搜索路径，相当于makefile里面的-I
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_subdirectory(src)

