cmake_minimum_required(VERSION 3.25)

project(3DEngine
    VERSION 3.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Platform detection
if(WIN32)
    message(STATUS "Building for Windows")
    add_compile_definitions(PLATFORM_WINDOWS)
    # Enable automatic DLL copying
    cmake_policy(SET CMP0087 NEW)
elseif(UNIX AND NOT APPLE)
    message(STATUS "Building for Linux")
    add_compile_definitions(PLATFORM_LINUX)
endif()

# Find required packages
find_package(PkgConfig)

if(WIN32)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(GTest CONFIG REQUIRED)
    find_package(glad CONFIG REQUIRED)
    find_package(glm CONFIG REQUIRED)
    find_package(assimp CONFIG REQUIRED)
    find_package(Bullet CONFIG REQUIRED)
else()
    # if(PkgConfig_FOUND)
    # endif()
endif()

add_subdirectory(src)

add_subdirectory(examples)