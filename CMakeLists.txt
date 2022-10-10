cmake_minimum_required(VERSION 3.23)
project(Proyecto2_MP)

set(CMAKE_CXX_STANDARD 14)

add_executable(Proyecto2_MP main.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Proyecto2_MP Threads::Threads)