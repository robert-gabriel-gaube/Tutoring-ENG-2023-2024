project(compression)
cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 17)

file(GLOB SOURCES
     "./include/*.h"
     "./src/*.c"
)
add_executable(compression ${SOURCES})

target_link_libraries(compression m)
target_include_directories(compression PUBLIC include)
