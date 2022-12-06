cmake_minimum_required(VERSION 3.10)

# set the project name
project(qt_word)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# 为Qt目标自动处理moc。
set(CMAKE_AUTOMOC ON)

# 搜索Qt4相关库
find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})

# add the executable
add_executable(${PROJECT_NAME}
            qt_word.cpp     
            word_operator.cpp)

target_link_libraries(${PROJECT_NAME} 
                    ${QT_LIBRARIES} Qt4::QAxContainer)

if (MSVC)
    # 设置 msvc 输入代码编码格式为 utf-8
    set(CMAKE_C_FLAGS /source-charset:utf-8)
endif()

# 如果需要运行别的目录的CMakeLists.txt， settings.json目录改下"cmake.sourceDirectory"， 然后删除build目录下的临时目录，
# Ctrl + Shift + P, CMake重现配置下，就可以build了。

# 或者 settings.json目录改下"cmake.sourceDirectory"， 编辑“CMake缓存”中的 CMAKE_HOME_DICTIONARY ；然后重新 cmake构建一下。
