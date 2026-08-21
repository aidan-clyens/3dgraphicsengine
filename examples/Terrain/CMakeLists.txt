project(TerrainExample)

add_executable(${PROJECT_NAME} Terrain.cpp)
target_link_libraries(${PROJECT_NAME} Engine Mesh)