# Library Dependency Graph

```mermaid
graph TD
  glm("glm")
  glad("glad")
  glfw("glfw")
  assimp("assimp")
  imgui("imgui")
  bullet3("bullet3")

  Core("Core")
  ECS("ECS")
  Engine("Engine")
  Mesh("Mesh")
  Texture("Texture")

  Core --> glm

  ECS --> glm
  ECS --> glad
  ECS --> glfw
  ECS --> assimp

  ECS --> Core

  Mesh --> Core
  Mesh --> ECS

  Texture --> glad
  Texture --> glfw

  Texture --> Core
  Texture --> ECS

  Engine --> glm
  Engine --> glad
  Engine --> glfw
  Engine --> imgui
  Engine --> bullet3

  Engine --> Core
  Engine --> Mesh
  Engine --> ECS
  Engine --> Texture
```