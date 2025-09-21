cmake_minimum_required(VERSION 3.28)

project(Chinese_Chess)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE CHINESE_CHESS_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
list(FILTER CHINESE_CHESS_SOURCES EXCLUDE REGEX "src/main.cpp$")
# set(CHINESE_CHESS_SOURCES
#     ${CMAKE_SOURCE_DIR}/src/main.cpp
#     ${CMAKE_SOURCE_DIR}/src/Game.cpp
#     ${CMAKE_SOURCE_DIR}/src/GameModeFactory.cpp
#     ${CMAKE_SOURCE_DIR}/src/StandardPveMode.cpp
# )

set(CHINESE_CHESS_INCLUDE
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(chinese_chess ${CHINESE_CHESS_SOURCES} src/main.cpp)
target_include_directories(chinese_chess PRIVATE ${CHINESE_CHESS_INCLUDE})

if (MINGW) 
    # 静态链接
    target_link_options(chinese_chess PRIVATE -static)
endif()

if (NOT CMAKE_BUILD_TYPE) 
    set(CMAKE_BUILD_TYPE Release)
endif()

message(STATUS "配置 ${CMAKE_BUILD_TYPE} 构建")
if (CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(chinese_chess PRIVATE -O3 -DNDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(chinese_chess PRIVATE -O0 -g)
endif()

option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS) 
    message(STATUS "启用单元测试")
    enable_testing()
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif()