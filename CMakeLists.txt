cmake_minimum_required(VERSION 3.27)
project(VulkanApp)

set(CMAKE_CXX_STANDARD 17)
set(GLSL_COMPILER "glslc")

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(Boost REQUIRED)
find_package(assimp CONFIG REQUIRED)

include_directories("/usr/include/stb/")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG__)
endif ()

#add_compile_definitions(SQUARE_EXAMPLE)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/shaders")
message(STATUS "Compiling vertex shader")
execute_process(COMMAND bash -c "${GLSL_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader.vert -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/vert.spv"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        RESULT_VARIABLE GLSL_COMPILE)
if (NOT ${GLSL_COMPILE} MATCHES 0)
    message(FATAL_ERROR "Error compiling vertex shader")
endif ()

message(STATUS "Compiling fragment shader")
execute_process(COMMAND bash -c "${GLSL_COMPILER} ${CMAKE_CURRENT_SOURCE_DIR}/shaders/shader.frag -o ${CMAKE_CURRENT_BINARY_DIR}/shaders/frag.spv"
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
        RESULT_VARIABLE GLSL_COMPILE)
if (NOT ${GLSL_COMPILE} MATCHES 0)
    message(FATAL_ERROR "Error compiling fragment shader")
endif ()

message(STATUS "Copying textures")
file(COPY assets/textures DESTINATION ${CMAKE_BINARY_DIR}/assets)
message(STATUS "Copying models")
file(COPY assets/models DESTINATION ${CMAKE_BINARY_DIR}/assets)

add_executable(VulkanApp main.cpp
        VulkanApplication.cpp
        VulkanApplication.h
        Global.h
        Shader.cpp
        Shader.h
)
target_link_libraries(VulkanApp Vulkan::Vulkan)
target_link_libraries(VulkanApp glfw)
target_link_libraries(VulkanApp Boost::boost)
target_link_libraries(VulkanApp assimp::assimp)
