cmake_minimum_required(VERSION 3.10)

project(TPE_Arqui)

set(CMAKE_C_STANDARD 11)

include_directories(Kernel/include)

file(GLOB SOURCES "Kernel/*.c")
file(GLOB HEADERS "Kernel/include/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})