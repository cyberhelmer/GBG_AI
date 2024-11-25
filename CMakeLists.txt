cmake_minimum_required(VERSION 3.20)
project(GBG_AI)

# Set C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


# Add source files and executables
add_executable(GBG_AI main.cpp)

target_include_directories(GBG_AI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)



