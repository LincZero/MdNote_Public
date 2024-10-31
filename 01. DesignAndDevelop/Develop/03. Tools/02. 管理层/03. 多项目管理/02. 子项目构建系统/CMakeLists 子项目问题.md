# CMakeLists 子项目问题

## 关键语法

```cmake
add_subdirectory(src)
```

## 实战举例 - TSDB

/CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.5)
project(TimeSeriesDB C)

set(CMAKE_C_STANDARD 11)

# Install路径
# 这里的相对路径是相对与build文件夹的。这里就在当前项目生成，就不生成到系统路径上了
# 另外不知道为什么，这个设置放不进子CMakeLists.txt里，放进去的路径是不对了
set(CMAKE_INSTALL_PREFIX "../")

# 添加子项目
add_subdirectory(src)
add_subdirectory(examples)
add_subdirectory(tests)
```

/src/CMakeLists.txt

```cmake
# 编译静态库
file(GLOB TSDB_SRC *.c *.cpp) # 抓取当前目录下的所有.c文件
add_library(TSDB ${TSDB_SRC})
set_target_properties(TSDB PROPERTIES
    # set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
)

# Install路径
# 这里的相对路径是相对与build文件夹的。这里就在当前项目生成，就不生成到系统路径上了
# 另外不知道为什么，这个设置放不进子CMakeLists.txt里，放进去的路径是不对了
set(CMAKE_INSTALL_PREFIX "../")

# 库安装以及依赖生成 (包括: 库、头文件依赖)
install(DIRECTORY ./ DESTINATION include
        FILES_MATCHING PATTERN "*.h")
install(TARGETS TSDB DESTINATION lib)
# file(GLOB HEADER_FILES "src/*.h") # 旧版，不能递归
# install(FILES ${HEADER_FILES} DESTINATION include) # 旧版，不能递归
```

/examples/CMakeLists.txt

```cmake
add_executable(Example ./example.c)

# 依赖相关
add_dependencies(Example TSDB) # 库依赖
include_directories(${PROJECT_SOURCE_DIR}/include) # 头文件依赖
# target_link_libraries(Example PRIVATE TSDB) # 链接TSDB库
target_link_libraries(Example PRIVATE ${PROJECT_SOURCE_DIR}/lib/libTSDB.a) # 链接TSDB库 (相对路径版)

# 生成输出
set_target_properties(Example PROPERTIES
    # set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/examples
)
install(TARGETS Example DESTINATION bin)
```

/tests/CmakeLists.txt

```cmake
# 编译单元测试程序
# include_directories(${PROJECT_SOURCE_DIR}/include) # 头文件依赖
# add_dependencies(Test TSDB) # 库依赖
#
# enable_testing() # 开启CTest测试系统
# add_executable(test_library tests/test_library.c)
# target_link_libraries(test_library PRIVATE TimeSeriesDB)
# add_test(NAME LibraryTest COMMAND test_library) # 添加测试
# set_target_properties(test_library PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/example
# )

#############################################

enable_testing() # 开启CTest测试系统
add_executable(Test ./test.c)

# 依赖相关
add_dependencies(Test TSDB) # 库依赖
include_directories(${PROJECT_SOURCE_DIR}/include) # 头文件依赖
target_link_libraries(Test PRIVATE ${PROJECT_SOURCE_DIR}/lib/libTSDB.a) # 链接TSDB库

# 生成输出
set_target_properties(Example PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/test
        )
install(TARGETS Test DESTINATION bin)
```

## 实战举例 - Recorder

/CMakeLists.txt

```cmake
cmake_minimum_required(VERSION 3.5)

# 使用缓存节省编译时间
find_program(CCACHE_FOUND ccache)
if (CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif ()

set(PROJECT_NAME recorder)

set(PROJECT_VERSION 4.2.7)

# 项目名和版本号
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION})

# c++11 (最低g++-4.8)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 11)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
include(utils)

# Checks for header files
check_header("stdbool.h")
check_header("stdint.h")
check_header("stdatomic.h")
check_header("sys/types.h")
check_header("sys/stat.h")
check_header("sys/time.h")
check_header("fcntl.h")
check_header("pthread.h")
check_header("endian.h")
check_header("sys/endian.h")

# Checks for functions
if (NOT MSVC)
    set(CMAKE_REQUIRED_LIBRARIES "-pthread")
endif ()
check_function("gettid" "unistd.h")
check_function("strlcpy" "string.h")
check_function("strlcat" "string.h")
check_function("clock_gettime" "time.h")
check_function("gettimeofday" "sys/time.h")
check_function("pthread_spin_lock" "pthread.h")
check_function("pthread_mutex_timedlock" "pthread.h")
check_function("sem_timedwait" "semaphore.h")
check_function("pipe" "unistd.h")
check_function("socketpair" "sys/socket.h")
check_function("eventfd" "sys/eventfd.h")
check_function("setproctitle" "unistd.h")

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/hconfig.h.in hconfig.h)

#编译后, 会在${PROJECT_BINARY_DIR}里生成config.h文件
string(TIMESTAMP COMPILE_DATA %Y%m%d)
string(TIMESTAMP COMPILE_TIME %H%M%S)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in config.h)

# 将目录下的所有源文件包含进SRCS中
file(GLOB_RECURSE SRCS src/*.cpp src/*.c)

# 将目录下的所有头文件包含进PROJECT_BINARY_DIR中
include_sub_directories_recursively(${PROJECT_SOURCE_DIR}/src)

# project
if (ANDROID)
    add_library(${PROJECT_NAME} SHARED main.cpp ${SRCS})
else ()
    add_executable(${PROJECT_NAME} main.cpp ${SRCS})
endif ()

# 链接库
if (ANDROID)
    set(LIBS ${LIBS} log android)
elseif (UNIX)
    set(LIBS ${LIBS} pthread m dl)
    if (CMAKE_COMPILER_IS_GNUCC)
        set(LIBS ${LIBS} rt)
    endif ()
endif ()

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0600)
    set(LIBS ${LIBS} winmm iphlpapi ws2_32 pathcch)
endif ()

if (APPLE)
    set(LIBS ${LIBS} "-framework CoreFoundation" "-framework Security")
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBS})

if (DEFINED CMAKE_BUILD_TYPE AND CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug mode is active")
    # 输出详细信息
    set(CMAKE_VERBOSE_MAKEFILE ON)
    #    target_compile_definitions(${PROJECT_NAME} PRIVATE PRINT_DEBUG) # libhv详细输出
else ()
    message("Debug mode is not active")
endif ()

target_compile_definitions(${PROJECT_NAME} PRIVATE PRINT_ERROR)

if (MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE NOMINMAX)
    target_compile_definitions(${PROJECT_NAME} PRIVATE HV_SOURCE)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:DebugDLL>") # Debug用DLL运行库，Release用静态链接运行库
endif ()

if (MINGW)
    # 启用静态运行时
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -static-libgcc -static-libstdc++")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -static-libgcc")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -static")
endif ()

# include
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR})

if (NOT ANDROID)
    add_subdirectory(demo)

    # 更新前端文件
    message("update web files")
    file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/web/)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/web/)
    file(COPY ${PROJECT_SOURCE_DIR}/web/release/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/web/)
endif ()
```

/demo/CMakeLists.txt

```cmake
#demo
add_executable(log_demo ./log_demo.cpp ${SRCS})
target_link_libraries(log_demo PRIVATE pthread ${LIBS})
target_include_directories(log_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(event_loop_demo ./event_loop_demo.cpp ${SRCS})
target_link_libraries(event_loop_demo PRIVATE pthread ${LIBS})
target_include_directories(event_loop_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(event_loop_thread_demo ./event_loop_thread_demo.cpp ${SRCS})
target_link_libraries(event_loop_thread_demo PRIVATE pthread ${LIBS})
target_include_directories(event_loop_thread_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(event_loop_thread_pool_demo ./event_loop_thread_pool_demo.cpp ${SRCS})
target_link_libraries(event_loop_thread_pool_demo PRIVATE pthread ${LIBS})
target_include_directories(event_loop_thread_pool_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(tcp_server_demo ./tcp_server_demo.cpp ${SRCS})
target_link_libraries(tcp_server_demo PRIVATE pthread ${LIBS})
target_include_directories(tcp_server_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(tcp_client_demo ./tcp_client_demo.cpp ${SRCS})
target_link_libraries(tcp_client_demo PRIVATE pthread ${LIBS})
target_include_directories(tcp_client_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(udp_server_demo ./udp_server_demo.cpp ${SRCS})
target_link_libraries(udp_server_demo PRIVATE pthread ${LIBS})
target_include_directories(udp_server_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(udp_client_demo ./udp_client_demo.cpp ${SRCS})
target_link_libraries(udp_client_demo PRIVATE pthread ${LIBS})
target_include_directories(udp_client_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(http_server_demo ./http_server_demo.cpp ${SRCS})
target_link_libraries(http_server_demo PRIVATE pthread ${LIBS})
target_include_directories(http_server_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(json_schema_demo ./json_schema_demo.cpp ${SRCS})
target_link_libraries(json_schema_demo PRIVATE pthread ${LIBS})
target_include_directories(json_schema_demo PRIVATE ${PROJECT_BINARY_DIR})

add_executable(ftp_demo ./ftp_demo.c ${SRCS})
target_link_libraries(ftp_demo PRIVATE pthread ${LIBS})
target_include_directories(ftp_demo PRIVATE ${PROJECT_BINARY_DIR})
```

















