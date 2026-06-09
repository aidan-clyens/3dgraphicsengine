project(Engine)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
  PUBLIC
  FILE_SET HEADERS
    BASE_DIRS
      ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES
        include/Camera.h
        include/Clock.h
        include/DebugWindow.h
        include/Engine.h
        include/InputManager.h
        include/Light.h
        include/Object3D.h
        include/Physics.h
        include/Renderer.h
        include/Rigidbody.h
        include/DynamicCharacterController.h
)

target_sources(${PROJECT_NAME} PRIVATE
    src/Camera.cpp
    src/Clock.cpp
    src/DebugWindow.cpp
    src/Engine.cpp
    src/InputManager.cpp
    src/Light.cpp
    src/Object3D.cpp
    src/Physics.cpp
    src/Renderer.cpp
    src/Rigidbody.cpp
    src/DynamicCharacterController.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Core
    ECS
    Texture
    Mesh
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    glfw glad::glad glm::glm assimp::assimp imgui::imgui BulletDynamics BulletCollision LinearMath ${GLFW_LIBRARIES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)