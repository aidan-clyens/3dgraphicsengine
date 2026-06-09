project(CharacterControllerExample)

add_executable(${PROJECT_NAME} CharacterController.cpp)
target_link_libraries(${PROJECT_NAME} Engine)