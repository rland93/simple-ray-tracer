cmake_minimum_required(VERSION 3.0.0)
project(simple-ray-tracer VERSION 0.1.0)

cmake_minimum_required (VERSION 3.1)

if(MSVC)
  add_compile_options(/W4)
else()
  add_compile_options(-Wall -Wextra)
endif()

include(CTest)
enable_testing()

add_executable(simple-ray-tracer src/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)