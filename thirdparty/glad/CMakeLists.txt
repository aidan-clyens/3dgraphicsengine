project(glad)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
        include/glad/gl.h
        include/KHR/khrplatform.h
)

target_sources(${PROJECT_NAME} PRIVATE
    src/gl.c
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)