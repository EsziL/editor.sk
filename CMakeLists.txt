cmake_minimum_required(VERSION 3.10)

project(editor.sk VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4)

add_executable(editor.sk src/main.cpp)

target_include_directories(editor.sk PRIVATE ${GTK4_INCLUDE_DIRS})

target_link_libraries(editor.sk PRIVATE ${GTK4_LIBRARIES})

target_compile_options(editor.sk PRIVATE ${GTK4_CFLAGS_OTHER})
