project(Mesh)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
        include/CubeMesh.h
        include/SquareMesh.h
        include/CircleMesh.h
        include/GridMesh.h
)

target_sources(${PROJECT_NAME} PRIVATE
    src/CubeMesh.cpp
    src/SquareMesh.cpp
    src/CircleMesh.cpp
    src/GridMesh.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  Core
  ECS
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)