project(RigidBodyExample)

add_executable(${PROJECT_NAME} RigidBody.cpp)
target_link_libraries(${PROJECT_NAME} Engine)