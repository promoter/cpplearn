cmake_minimum_required(VERSION 3.10)

# set the project name
project(libevent_udp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 为Qt目标自动处理moc。
set(CMAKE_AUTOMOC ON)

# 搜索Qt4相关库
find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})

set(LIBEVENT_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libevent/lib")
set(LIBEVENT_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libevent/include")

include_directories(${LIBEVENT_INCLUDE_PATH})

# add the executable
add_executable(${PROJECT_NAME}
            main.cpp
            udp_multicast.cpp)

target_link_libraries(${PROJECT_NAME} 
                ${QT_LIBRARIES} 
                "${LIBEVENT_LIB_PATH}/libevent.lib")

if (MSVC)
    # 设置 msvc 输入代码编码格式为 utf-8
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()
