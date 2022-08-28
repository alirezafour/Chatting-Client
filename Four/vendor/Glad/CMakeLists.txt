# Silence warning about PROJECT_VERSION
cmake_policy(SET CMP0048 NEW)

# Enable MACOSX_RPATH by default
cmake_policy(SET CMP0042 NEW)

# Allow "IN_LIST" in "IF()"
cmake_policy(SET CMP0057 NEW)

if(NOT CMAKE_VERSION VERSION_LESS 3.1)
  # Silence warning about if()
  cmake_policy(SET CMP0054 NEW)
endif()

if(CMAKE_VERSION VERSION_GREATER 3.8)
  # Enable IPO for CMake versions that support it
  cmake_policy(SET CMP0069 NEW)
endif()

project(Glad)
cmake_minimum_required(VERSION 3.5)

include_directories(include)

file(GLOB Glad_SRC
    "include/glad/glad.h"
    "include/KHR/khrplatform.h"

    "src/glad.c"
)

add_library(glad STATIC ${Glad_SRC})

