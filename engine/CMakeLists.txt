cmake_minimum_required(VERSION 2.8)
project(Engine)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(include)

add_subdirectory(src)

add_library(

  engine
  SHARED
  main.cc

)
