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

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/imgui_demo.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/imgui_tables.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_glfw.cpp
    ${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/thirdparty/imgui>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/thirdparty/imgui/backends>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/thirdparty/bullet3/src>
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Core
    ECS
    Texture
    Mesh
)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC
        glfw glad glm assimp::assimp BulletDynamics BulletCollision LinearMath ${GLFW_LIBRARIES}
    )
else()
    target_link_libraries(${PROJECT_NAME} PUBLIC
        glfw glad glm assimp BulletDynamics BulletCollision LinearMath ${GLFW_LIBRARIES}
    )
endif()


set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)