cmake_minimum_required(VERSION 3.10)

project(Terminal-Calculator VERSION 1.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

set(TARGET calculator)

add_executable(${TARGET}
	src/main.c
	src/calculator.c
)

target_include_directories(${TARGET} PRIVATE src)

target_link_libraries(${TARGET} m)
