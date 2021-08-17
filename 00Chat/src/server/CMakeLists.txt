# (2) 配置编译选项
#加上代表可执行文件可以调试
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
# 设置c++版本
set(CMAKE_CXX_STANDARD 11)

# (3') 设定src目录下的所有源文件 保存到 SRC_LIST 变量
# 把指定路径下的所有源文件名字放到变量名 SRC_LIST 中 .代表当前路径下的文件 src代表src文件夹下的文件
aux_source_directory(. SRC_LIST)
aux_source_directory(./db DB_LIST)

# (3')设置需要编译的源文件列表
# set(SRC_LIST1 cmake_moduo.cpp)

# (3)指定源文件 和 生成可执行目标的名字
# 将名为 cmake_moduo.cpp test.cpp 的源文件编译成一个名称为 cmake_moduo 的可执行文件
#add_executable(cmake_moduo cmake_moduo.cpp test.cpp)

# (3) 指定源文件 和 生成可执行目标的名字
# 将名为 SRC_LIST 变量 的所有源文件编译成一个名称为 Chat_Server 的可执行文件
add_executable(Chat_Server ${SRC_LIST} ${DB_LIST})

# (6) 需要链接的库。 目标程序，需要链接这4个库文件
target_link_libraries(Chat_Server muduo_net muduo_base mysqlclient pthread)



