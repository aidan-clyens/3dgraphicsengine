project(ECS)

add_library(${PROJECT_NAME} ECS.cpp Mesh.cpp MeshInstances.cpp Model.cpp Rigidbody.cpp DynamicCharacterController.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../../../include)
target_link_libraries(${PROJECT_NAME} glfw glad::glad glm::glm assimp::assimp BulletDynamics BulletCollision LinearMath ${GLFW_LIBRARIES})