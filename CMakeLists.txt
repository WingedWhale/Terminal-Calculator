cmake_minimum_required(VERSION 3.28.3)
project(Terminal-Calculator)

add_executable(${PROJECT_NAME} main.c)
add_library(calculator calculator.c)

find_package(math)

target_link_libraries(${PROJECT_NAME} calculator math)
