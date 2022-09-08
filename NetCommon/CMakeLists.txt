
# Silence warning about PROJECT_VERSION
cmake_policy(SET CMP0048 NEW)


project(NetCommon VERSION 0.0.1 LANGUAGES CXX)
cmake_minimum_required(VERSION 3.16)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(src)
include_directories(vendor/asio/asio/include)


file(GLOB NetCommon_SRC
     "src/*.h"
)
