cmake_minimum_required(VERSION 3.10)
project(UDPCommunication)

# 设置C编译器标准
set(CMAKE_C_STANDARD 11)

# 添加可执行文件，指定源文件
add_executable(sender sender/sender.cpp)
add_executable(receiver receiver/receiver.cpp)

# 添加头文件目录
target_include_directories(sender PUBLIC sender)
target_include_directories(receiver PUBLIC receiver)
