# 设置最低版本要求
cmake_minimum_required(VERSION 2.8)

#项目名称
project(sylar_cnzed)

# 打开详细的makefile输出
set(CMAKE_VERBOSE_MAKEFILE ON)
# 设置C++编译标志，包括从环境变量继承的标志，以及其他编译选项
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined")

# 包含当前目录下的头文件
include_directories(.)

# 包含指定路径下的头文件
include_directories(/apps/bread/include)

# 链接指定路径下的库文件
link_directories(/apps/bread/lib)

# 定义库的源文件列表
set(LIB_SRC
    sylar/config.cc
    sylar/fiber.cc
    sylar/iomanager.cc
    sylar/log.cc
    sylar/scheduler.cc
    sylar/thread.cc
    sylar/util.cc
)

# 创建共享库sylar，包含上面定义的源文件
add_library(sylar_cnzed SHARED ${LIB_SRC})

# 查找yaml-cpp库并将结果存储在YAMLCPP变量中
find_library(YAML_CPP yaml-cpp)
find_library(PTHREAD pthread)
# 输出找到的yaml-cpp库路径
message("*** ${YAMLCPP}")

set(LIBS
        sylar_cnzed
        pthread
        yaml-cpp)
        
message("***", ${LIBS})

# 创建可执行文件test，源文件为tests/test.cc
add_executable(test tests/test.cc)

# 设置test依赖于sylar_cnzed库
add_dependencies(test sylar_cnzed)

add_executable(test_config tests/test_config.cc)
add_dependencies(test_config sylar_cnzed)
# 链接test_config可执行文件与sylar_cnzed库和yaml-cpp库
target_link_libraries(test_config sylar_cnzed ${LIBS})

# 创建可执行文件testlog，源文件为tests/teslog.cc
add_executable(testlog tests/testlog.cc)

# 设置testlog依赖于sylar_cnzed库
add_dependencies(testlog sylar_cnzed)

# 链接testlog可执行文件与sylar库和yaml-cpp库
target_link_libraries(testlog sylar_cnzed ${LIBS})

add_executable(test_thread tests/test_thread.cc)
add_dependencies(test_thread sylar_cnzed)
target_link_libraries(test_thread ${LIBS})

add_executable(test_util tests/test_util.cc)
add_dependencies(test_util sylar_cnzed)
target_link_libraries(test_util ${LIBS})

add_executable(test_fiber tests/test_fiber.cc)
add_dependencies(test_fiber sylar_cnzed)
target_link_libraries(test_fiber ${LIBS})

add_executable(test_scheduler tests/test_scheduler.cc)
add_dependencies(test_scheduler sylar_cnzed)
target_link_libraries(test_scheduler ${LIBS})

add_executable(test_iomanager tests/test_iomanager.cc)
add_dependencies(test_iomanager sylar_cnzed)
target_link_libraries(test_iomanager ${LIBS})

# 设置所有可执行文件的输出路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

# 设置所有库文件的输出路径
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
