project(Primitives)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
        include/Cube.h
        include/Square.h
        include/Circle.h
)

target_sources(${PROJECT_NAME} PRIVATE
    src/Cube.cpp
    src/Square.cpp
    src/Circle.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Texture
    Mesh
    Engine
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)