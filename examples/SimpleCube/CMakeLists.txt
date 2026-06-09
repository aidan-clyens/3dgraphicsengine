project(SimpleCubeExample)

add_executable(${PROJECT_NAME} SimpleCube.cpp)
target_link_libraries(${PROJECT_NAME} Engine)