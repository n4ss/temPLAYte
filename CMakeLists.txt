cmake_minimum_required(VERSION 2.8)

project(graph)

set(OS_NAME ${CMAKE_SYSTEM_NAME})
execute_process(COMMAND uname -m OUTPUT_VARIABLE ARCH_NAME)
string(STRIP "${ARCH_NAME}" ARCH_NAME)
string(TOUPPER "${ARCH_NAME}" ARCH_NAME)

if ("${ARCH_NAME}" MATCHES "I386")
	set(ARCH_NAME "X86")
endif ()

message("Building for target ${OS_NAME}-${ARCH_NAME}")

set(CMAKE_CXX_COMPILER	"g++")

set(TARGET_COMMON_SOURCES
	Sources/main.cpp
	)

set(TARGET_SOURCES ${TARGET_COMMON_SOURCES})

include_directories(Headers)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -Wno-unused-parameter")

add_executable(graph ${TARGET_SOURCES})
