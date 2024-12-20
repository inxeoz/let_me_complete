cmake_minimum_required(VERSION 3.16)
project(let_me_practice)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_BUILD_TYPE Debug)

set(SOURCES
        main.cpp
        simple_rust/Lexer.cpp
        simple_rust/Parser.cpp
        simple_rust/CodeGenerator.cpp
        llvmapi/SimpleLLVM.cpp
)

add_executable(let_me_practice ${SOURCES})


# Find LLVM package
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Include LLVM directories

include_directories(${CMAKE_SOURCE_DIR}/cppllvm)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Use llvm-config to link required LLVM libraries
execute_process(COMMAND llvm-config --libs interpreter executionengine core target irreader analysis
        OUTPUT_VARIABLE LLVM_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(COMMAND llvm-config --system-libs
        OUTPUT_VARIABLE LLVM_SYSTEM_LIBS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(COMMAND llvm-config --ldflags
        OUTPUT_VARIABLE LLVM_LDFLAGS
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Set the linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LLVM_LDFLAGS}")

# Link all required libraries
target_link_libraries(let_me_practice ${LLVM_LIBS} ${LLVM_SYSTEM_LIBS})
