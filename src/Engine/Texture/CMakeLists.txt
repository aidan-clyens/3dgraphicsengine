project(Texture)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
        include/DepthTexture.h
        include/Texture.h
        include/Texture2D.h
        include/TextureCubeMap.h
)

target_sources(${PROJECT_NAME} PRIVATE
  src/DepthTexture.cpp
  src/Texture.cpp
  src/Texture2D.cpp
  src/TextureCubeMap.cpp
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


target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw glad::glad glm::glm assimp::assimp BulletDynamics BulletCollision LinearMath ${GLFW_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)