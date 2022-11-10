cmake_minimum_required(VERSION 3.0)

set(myproject "PAOO")

add_subdirectory(src)

add_executable("${PROJECT_NAME}" main.cpp)

