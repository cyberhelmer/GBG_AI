cmake_minimum_required(VERSION 3.20)
project(MyExistingProject)

# Set C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files and executables
add_executable(MyExecutableName main.cpp)
