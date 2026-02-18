cmake_minimum_required(VERSION 3.21)

project(GravitySim)
set(TargetName 2Dsim)

# dependencies
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

set(DEPS glfw glm::glm)

add_executable(${TargetName} src/GravitySim.cpp src/glad.c)

target_link_libraries(${TargetName} PRIVATE ${DEPS})
target_include_directories(${TargetName} PRIVATE src)