cmake_minimum_required(VERSION 3.10)

project(TPE_Arqui)

set(CMAKE_C_STANDARD 11)

file(GLOB KERNEL_SOURCES "Kernel/*.c")
file(GLOB KERNEL_HEADERS "Kernel/include/*.h")

file(GLOB USERLAND_SOURCES "Userland/SampleCodeModule/*.c")
file(GLOB USERLAND_HEADERS "Userland/SampleCodeModule/include/*.h")

# Add the Kernel include directory globally
include_directories(Kernel/include)

# Add the Userland include directory globally
include_directories(Userland/SampleCodeModule/include)

# Create the Kernel target
add_executable(KernelTarget ${KERNEL_SOURCES})
target_include_directories(KernelTarget PRIVATE ${KERNEL_HEADERS})
target_link_libraries(KernelTarget PRIVATE -nostdlib)

# Create the Userland target
add_executable(UserlandTarget ${USERLAND_SOURCES})
target_include_directories(UserlandTarget PRIVATE ${USERLAND_HEADERS})
target_link_libraries(UserlandTarget PRIVATE -nostdlib)
