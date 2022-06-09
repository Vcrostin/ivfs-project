cmake_minimum_required(VERSION 3.22)
project(IVFSproject)

set(CMAKE_CXX_STANDARD 20)

add_executable(IVFSproject main.cpp ivfs.cpp ivfs.h utils.cpp utils.h)
