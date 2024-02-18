cmake_minimum_required(VERSION 3.12)
project(Pybind11Example LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -mavx -fopenmp -pipe /openmp:llvm /EHsc")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Python
# find_package(Python REQUIRED COMPONENTS Development)
find_package(Python 3.10 COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG)
# Set the path to Pybind11
# set(PYBIND11_DIR /path/to/pybind11)
# add_subdirectory(${PYBIND11_DIR} ${CMAKE_BINARY_DIR}/pybind11)

# Include directories
# include_directories(${PYBIND11_DIR} ${CMAKE_SOURCE_DIR}/include)

# Collect all source files in the src directory
file(GLOB SOURCES src/*.cpp tools/*.cpp)

# Create the shared library
pybind11_add_module(harvest_lib ${SOURCES})

# Link the Python development library
target_link_libraries(harvest_lib PRIVATE Python::Python)
target_include_directories(harvest_lib PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tools)

# add_executable(test test/test.cpp ${SOURCES})
# target_include_directories(test PUBLIC ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/tools)
# target_link_libraries(test STATIC example)