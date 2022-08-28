# Silence warning about PROJECT_VERSION
cmake_policy(SET CMP0048 NEW)

#project setup
project(Four VERSION 0.0.1 LANGUAGES CXX)
cmake_minimum_required(VERSION 3.16)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# multi process compiling
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")

# set as shared library
#option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# add includes
include_directories(src)
include_directories(vendor/spdlog/include)
include_directories(vendor/Glad/include)
include_directories(vendor/GLFW/include)
include_directories(vendor/ImGui)

add_subdirectory(vendor/GLFW)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/Glad)
add_subdirectory(vendor/ImGui)



file(GLOB Four_SRC
     "src/*.h"
     "src/*.cpp"

     "src/Four/*.h"
     "src/Four/*.cpp"
     "src/Four/Event/*.h"
     "src/Four/Event/*.cpp"
     "src/Four/ImGui/*.h"
     "src/Four/ImGui/*.cpp"

     "src/Platforms/*.h"
     "src/Platforms/*.cpp"
)

add_library(Four SHARED
        ${Four_SRC}
)

# pch header
target_precompile_headers(Four PUBLIC
    src/fourpch.h
    src/fourpch.cpp
)

target_link_libraries(Four PRIVATE glfw)
target_link_libraries(Four PRIVATE glad)
target_link_libraries(Four PRIVATE spdlog)
target_link_libraries(Four PRIVATE imgui)


#add_library(opengl32.lib STATIC IMPORTED)
#target_link_libraries(Four PRIVATE opengl32.lib)


add_compile_definitions(FOUR_PLATFORM_WINDOWS)
add_compile_definitions(FOUR_BUILD_DLL)
add_compile_definitions(GLFW_INCLUDE_NONE)
add_compile_definitions(USING_GLFW)


