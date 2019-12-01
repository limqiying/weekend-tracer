cmake_minimum_required(VERSION 3.15.4)
project(weekend-tracer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(include)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

file(GLOB SOURCES "src/*.cpp")

add_executable(weekend-tracer ${SOURCES})
target_link_libraries (weekend-tracer Eigen3::Eigen)