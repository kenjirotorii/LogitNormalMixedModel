cmake_minimum_required(VERSION 3.0)

project(LNMM)
set(PYBIND11_CPP_STANDARD -std=c++14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")
add_subdirectory(pybind11)

pybind11_add_module(LNMM utils.cpp models.cpp cpp2py.cpp)
