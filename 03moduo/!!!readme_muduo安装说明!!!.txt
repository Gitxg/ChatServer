https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980

编译并安装muuduo库
(1) 首先从github上面下载下来：
https://github.com/chenshuo/muduo

(2) 
采用build.sh源码编译构建程序，运行该程序.
muduo目录下运行
./build.sh

(3) 编译完成之后安装库文件
muduo目录下运行
./build.sh install

这个./build.sh install实际上把muduo的头文件和lib库文件
放到了muduo-master同级目录下的build目录下的release-install-cpp11文件夹下面了。

所以上面的install命令并没有把它们拷贝到系统路径下，导致我们每次编译程序都需要指定muduo库的头文件和库文件路径，
很麻烦，所以我们选择直接把inlcude（头文件）和lib（库文件）目录下的文件拷贝到系统目录下：
release-install-cpp11目录下依次cd include    cd lib
mv muduo/ /usr/include/
mv * /usr/local/lib/

拷贝完成以后使用muduo库编写C++网络程序，不用在指定头文件和lib库文件路径信息了，
因为g++会自动从/usr/include和/usr/local/lib路径下寻找所需要的文件。

