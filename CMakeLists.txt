cmake_minimum_required(VERSION 3.10)

# Project name and version
project(optichess VERSION 1.0 LANGUAGES C)

# Set the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add the public headers folder so that any #include "file.h" can find them.
# (Assumes headers are in optichess/includes)
include_directories(${PROJECT_SOURCE_DIR}/includes)

# Add subdirectories for your main source code and tests.
add_subdirectory(src)
# add_subdirectory(tests)