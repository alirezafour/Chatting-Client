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

# setup conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# set as shared library
#option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

# add includes
include_directories(
    src
)

file(GLOB SOURCES
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

     "src/Platforms/Windows/*.h"
     "src/Platforms/Windows/*.cpp"

)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

# pch header
target_precompile_headers(Four PUBLIC
    src/fourpch.h
    src/fourpch.cpp
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        CONAN_PKG::glfw
        CONAN_PKG::glad
        CONAN_PKG::imgui
        CONAN_PKG::spdlog
)

add_compile_definitions(
    FOUR_PLATFORM_WINDOWS
    FOUR_BUILD_DLL
    GLFW_INCLUDE_NONE
    USING_GLFW
)

target_include_directories(${PROJECT_NAME} 
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

