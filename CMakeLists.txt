cmake_minimum_required(VERSION 3.20)
project(GBG_AI)

# Set C++ standard to 20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Find and link libcurl
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

# Add source files and executables
add_executable(GBG_AI main.cpp)

target_include_directories(GBG_AI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
# Link libcurl to your project
target_link_libraries(GBG_AI PRIVATE ${CURL_LIBRARIES})



