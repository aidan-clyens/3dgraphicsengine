project(EngineCore)

add_subdirectory(Core)
add_subdirectory(ECS)
add_subdirectory(Texture)
add_subdirectory(Mesh)

set(SOURCES
    src/Engine.cpp
    src/Object3D.cpp
    src/Renderer.cpp
    src/InputManager.cpp
    src/Camera.cpp
    src/Shader.cpp
    src/Physics.cpp
    src/Light.cpp
    src/Clock.cpp
    src/DebugWindow.cpp
)

set(THIRDPARTY_DIR ../../thirdparty)
set(IMGUI_DIR ${THIRDPARTY_DIR}/imgui)

list(APPEND SOURCES
    ${IMGUI_DIR}/imgui.cpp ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp
)

list(APPEND SOURCES
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
# SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
# SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ../../include)
target_include_directories(${PROJECT_NAME} PUBLIC ${THIRDPARTY_DIR}/)
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_DIR}/backends)
target_link_libraries(${PROJECT_NAME} Core ECS Texture Mesh)
target_link_libraries(${PROJECT_NAME} glfw glad::glad glm::glm assimp::assimp BulletDynamics BulletCollision LinearMath ${GLFW_LIBRARIES})
