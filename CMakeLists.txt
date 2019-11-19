cmake_minimum_required(VERSION 3.10)  # CMake version check
project(risingCity)               # Create project "risingCity"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES main.cpp MinHeap.cpp MinHeap.h RBTree.cpp RBTree.h BSTree.cpp BSTree.h MyQueue.cpp MyQueue.h FileParser.cpp FileParser.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(risingCity ${SOURCE_FILES})