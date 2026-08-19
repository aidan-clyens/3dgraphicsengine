project(PrimitiveObjectsExample)

add_executable(${PROJECT_NAME} PrimitiveObjects.cpp)
target_link_libraries(${PROJECT_NAME} Engine Primitives)