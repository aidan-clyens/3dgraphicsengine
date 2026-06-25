project(Core)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
        include/LoadImage.h
        include/Timer.h
        include/Types.h
)

target_sources(${PROJECT_NAME} PRIVATE
    src/LoadImage.cpp
    src/Timer.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/thirdparty>
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glm::glm
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)