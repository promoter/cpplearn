cmake_minimum_required(VERSION 3.10)

# set the project name
project(test)

# add the executable
add_executable(${PROJECT_NAME}
            future.cpp     
            smart_pointer.cpp)

if (MSVC)
    # 设置 msvc 输入代码编码格式为 utf-8
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()
