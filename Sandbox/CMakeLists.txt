cmake_minimum_required(VERSION 3.16)

# Silence warning about PROJECT_VERSION
cmake_policy(SET CMP0048 NEW)

#project setup
project(Sandbox
		VERSION 0.0.1
		LANGUAGES CXX)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_CURRENT_BINARY_DIR}/bin)

include_directories(${PARENT_DIR}/src)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

file(GLOB SOURCES
     "src/*.h"
     "src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		Four
		CONAN_PKG::boost
		CONAN_PKG::imgui
		CONAN_PKG::spdlog
)

add_compile_definitions(FOUR_PLATFORM_WINDOWS)
add_compile_definitions(USING_GLFW)

file(MAKE_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/asserts)
add_custom_command(TARGET ${PROJECT_NAME}  POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/asserts
				${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/asserts
)

# Adding the tests:
option(ENABLE_TESTING "Enable the tests" ${PROJECT_IS_TOP_LEVEL})
if(true)
  enable_testing()
  #add_subdirectory(test)
endif()