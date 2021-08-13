
#       (1)  (2)                (3)          (4)            (5)        (6)
#g++ -o main -g -std=c++11 main.cpp xxx.cpp -I/usr/include -L/usr/lib -Imuduo_net -Imuduo_base -Ipthread

# (1')设置cmake的全局变量 设定输出文件的路径
# EXECUTABLE_OUTPUT_PATH 代表二进制可执行文件的输出位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# (2) 配置编译选项
#加上代表可执行文件可以调试
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
# 设置c++版本
set(CMAKE_CXX_STANDARD 11)

# (3') 设定src目录下的所有源文件 保存到 SRC_LIST 变量
# 把指定路径下的所有源文件名字放到变量名SRC_LIST中 .代表当前路径下的文件 src代表src文件夹下的文件
aux_source_directory(src SRC_LIST)

# (3)指定源文件 和 生成可执行目标的名字
# 将名为 cmake_moduo.cpp test.cpp 的源文件编译成一个名称为 cmake_moduo 的可执行文件
#add_executable(cmake_moduo cmake_moduo.cpp test.cpp)

# (3) 指定源文件 和 生成可执行目标的名字
# 将名为 SRC_LIST 变量 的所有源文件编译成一个名称为 cmake_moduo 的可执行文件
add_executable(cmake_moduo ${SRC_LIST})

# (4) 添加头文件的搜索路径，相当于makefile里面的-I
Include_directories(${PROJECT_SOURCE_DIR}/include)

# (5) 添加库文件的搜索路径，相当于makefile里面的-I
link_directories(${PROJECT_SOURCE_DIR}/lib)

# (6) 需要链接的库。 cmake_moduo这个目标程序，需要链接这三个库文件
target_link_libraries(cmake_moduo muduo_net muduo_base pthread)


