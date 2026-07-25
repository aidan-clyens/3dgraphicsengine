cmake_minimum_required(VERSION 3.25)

project(3dgraphicsengine
    VERSION 3.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Platform detection
if(WIN32)
    message(STATUS "Building for Windows")
    add_compile_definitions(PLATFORM_WINDOWS)
    cmake_policy(SET CMP0087 NEW)
elseif(UNIX AND NOT APPLE)
    message(STATUS "Building for Linux")
    add_compile_definitions(PLATFORM_LINUX)
endif()

# All third-party dependencies are vendored under thirdparty/ and built
# from source as static libraries so the installed package is self-contained.
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

if(UNIX AND NOT APPLE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

# GLFW vendoring options
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL ON CACHE BOOL "" FORCE)
if(UNIX AND NOT APPLE)
    set(GLFW_BUILD_WAYLAND ON CACHE BOOL "" FORCE)
    set(GLFW_BUILD_X11 ON CACHE BOOL "" FORCE)
endif()

# Assimp vendoring options
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/bullet3)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/assimp)

option(BUILD_TESTS "Build unit tests" OFF)
if(BUILD_TESTS)
    find_package(GTest CONFIG REQUIRED)
    enable_testing()
endif()

option(BUILD_EXAMPLES "Build examples" ON)

add_subdirectory(src)

if (BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# Installation settings
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Ship the default GLSL shaders as package data. Renderer resolves shader
# paths as <path>/shaders/*.glsl where <path> is the Engine constructor's
# 3rd argument (empty by default, resolved relative to the process's CWD) -
# consumers point that argument at wherever this directory ends up installed,
# or copy it next to their own executable.
install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/shaders
    DESTINATION ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}
)

# Install library targets and header files
install(
    TARGETS
        Engine
        Core
        ECS
        Texture
        Mesh
        glad
        glm
        glm-header-only
        BulletDynamics
        BulletCollision
        LinearMath
        glfw
        assimp
        zlibstatic
    EXPORT ${PROJECT_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# glm and Bullet don't install their own headers by default when vendored as
# a subdirectory (glm's install is gated behind GLM_BUILD_INSTALL, off for
# non-master projects; Bullet's INSTALL_LIBS defaults off for MSVC project
# files) but consumers still need them since Types.h/Physics.h/etc include
# them directly, so install the header trees ourselves.
install(
    DIRECTORY thirdparty/glm/glm
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PATTERN "CMakeLists.txt" EXCLUDE
)
install(
    DIRECTORY thirdparty/bullet3/src/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.h"
)

# imgui is compiled directly into Engine's sources rather than added as its
# own subdirectory/target, so its headers (referenced unprefixed, e.g.
# "imgui.h", by Engine's public DebugWindow.h) need installing explicitly too.
install(FILES
    thirdparty/imgui/imgui.h
    thirdparty/imgui/imconfig.h
    thirdparty/imgui/imgui_internal.h
    thirdparty/imgui/imstb_rectpack.h
    thirdparty/imgui/imstb_textedit.h
    thirdparty/imgui/imstb_truetype.h
    thirdparty/imgui/backends/imgui_impl_glfw.h
    thirdparty/imgui/backends/imgui_impl_opengl3.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export targets
install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Create package configuration file
set(3DGRAPHICSENGINE_SHADERS_INSTALL_DIR ${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/shaders)
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
    PATH_VARS 3DGRAPHICSENGINE_SHADERS_INSTALL_DIR
)

# Create package version file
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Install package configuration files
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# CPack packaging configuration
set(CPACK_PACKAGE_NAME "lib${PROJECT_NAME}")
set(CPACK_PACKAGE_VENDOR "Aidan Clyens")
set(CPACK_PACKAGE_CONTACT "Aidan Clyens <aidanclyens@gmail.com>")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "3D Graphics Engine C++ SDK")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_RELOCATABLE ON)
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr")

# Debian/Ubuntu packaging configuration
if(UNIX AND NOT APPLE)
    set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
    set(CPACK_DEBIAN_PACKAGE_NAME "lib${PROJECT_NAME}")
    set(CPACK_DEBIAN_FILE_NAME "DEB-DEFAULT")
    set(CPACK_DEBIAN_PACKAGE_VERSION ${PROJECT_VERSION})
    set(CPACK_DEBIAN_PACKAGE_RELEASE "1")
    set(CPACK_DEBIAN_PACKAGE_LICENSE "MIT")
    set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/aidan-clyens/3D-graphics-engine")
endif()

include(CPack)