cmake_minimum_required(VERSION 3.20.0)
set(CMAKE_CXX_STANDARD 11)

project(app)

find_package(glfw3 3.4 REQUIRED)

set(SOURCES main.cpp glad.c)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw)