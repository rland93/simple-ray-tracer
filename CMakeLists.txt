cmake_minimum_required(VERSION 3.0.0)
project(simple-ray-tracer VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(simple-ray-tracer src/main.cpp src/fresnel.cpp src/trace.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
