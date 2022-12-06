cmake_minimum_required(VERSION 3.10)

# set the project name
project(QuiKPlatform_)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 为Qt目标自动处理moc。
set(CMAKE_AUTOMOC ON)

# 搜索Qt4相关库
find_package(Qt4 REQUIRED)

set(QuiKPlatform_LIB_PATH "C:/Program Files (x86)/QuiKPlatform/lib/Win32/Debug")
set(QuiKPlatform_INCLUDE_PATH "C:/Program Files (x86)/QuiKPlatform/include")

include(${QT_USE_FILE})
include_directories(${QuiKPlatform_INCLUDE_PATH})

# add the executable
add_executable(${PROJECT_NAME}
            main.cpp
            CoreManTarget.cpp)

target_link_libraries(${PROJECT_NAME} 
                ${QT_LIBRARIES} 
                "${QuiKPlatform_LIB_PATH}/CoreLib.lib" 
                "${QuiKPlatform_LIB_PATH}/ToolsLib.lib"
                "${QuiKPlatform_LIB_PATH}/CoreApp.lib" 
                "${QuiKPlatform_LIB_PATH}/CoreUi.lib"
                "${QuiKPlatform_LIB_PATH}/KLWidgets.lib" )

if (MSVC)
    # 设置 msvc 输入代码编码格式为 utf-8
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()
