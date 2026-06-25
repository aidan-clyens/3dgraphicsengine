cmake_minimum_required(VERSION 3.25)

project(3Dgraphicsengine
    VERSION 3.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
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

add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)
add_subdirectory(thirdparty/bullet3)

if(WIN32)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(GTest CONFIG REQUIRED)
    find_package(glad CONFIG REQUIRED)
    find_package(glm CONFIG REQUIRED)
    find_package(assimp CONFIG REQUIRED)
    find_package(Bullet CONFIG REQUIRED)
    find_package(imgui CONFIG REQUIRED)
else()
    if(PkgConfig_FOUND)
        pkg_check_modules(glfw3 REQUIRED IMPORTED_TARGET glfw3)
        pkg_check_modules(assimp REQUIRED IMPORTED_TARGET assimp)
    endif()
    find_package(GTest REQUIRED)
endif()

add_subdirectory(src)
add_subdirectory(examples)

# Installation settings
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

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
    EXPORT ${PROJECT_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Export targets
install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Create package configuration file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
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