cmake_minimum_required(VERSION 3.16)
project(CppLearningCurriculum VERSION 1.0.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Include directories
include_directories(src)

# Core library
file(GLOB_RECURSE CORE_SOURCES "src/core/*.cpp")
file(GLOB_RECURSE UTILS_SOURCES "src/utils/*.cpp")

add_library(curriculum_core STATIC ${CORE_SOURCES} ${UTILS_SOURCES})

# Main application
add_executable(curriculum_app src/main.cpp)
target_link_libraries(curriculum_app curriculum_core)

# Test executable (if tests are added later)
option(BUILD_TESTS "Build test suite" OFF)
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Installation
install(TARGETS curriculum_app DESTINATION bin)
install(DIRECTORY modules/ DESTINATION share/curriculum/modules)
install(DIRECTORY exercises/ DESTINATION share/curriculum/exercises)
install(DIRECTORY projects/ DESTINATION share/curriculum/projects)
install(DIRECTORY assessments/ DESTINATION share/curriculum/assessments)
