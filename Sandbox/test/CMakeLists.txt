cmake_minimum_required(VERSION 3.16)

project(CmakeConfigTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()
  find_package(Sandbox CONFIG REQUIRED) # for intro, project_options, ...
endif()

# ---- Dependencies ----
get_filename_component(PARENT_DIR ../../ ABSOLUTE)
include_directories(${PARENT_DIR}/Four/vendor/spdlog/tests)

add_library(catch_main OBJECT catch_main.cpp)

add_executable(tests tests.cpp)
target_link_libraries(tests PRIVATE catch_main)

