project(LoadModelExample)

add_executable(${PROJECT_NAME} LoadModel.cpp)
target_link_libraries(${PROJECT_NAME} Engine)