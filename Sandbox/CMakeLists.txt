# Silence warning about PROJECT_VERSION
cmake_policy(SET CMP0048 NEW)


#project setup
project(Sandbox VERSION 0.0.1 LANGUAGES CXX)
cmake_minimum_required(VERSION 3.16)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR}/src)

include_directories(${PARENT_DIR}/Four/vendor/spdlog/include)
include_directories(${PARENT_DIR}/Four/vendor/imgui)

find_package(Boost)

file(GLOB SOURCES
     "src/*.h"
     "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC Four)

target_link_libraries(${PROJECT_NAME} PUBLIC Four)

target_include_directories(${PROJECT_NAME} 
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		${Boost_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${Boost_LIBRARIES}
)

add_compile_definitions(FOUR_PLATFORM_WINDOWS)
add_compile_definitions(USING_GLFW)

add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/asserts
                ${CMAKE_CURRENT_BINARY_DIR}/asserts)