# 3D Graphics Engine

A modular, component-based 3D game engine built with modern C++ and OpenGL, featuring an Entity-Component-System architecture, physics simulation, and advanced rendering capabilities.

## Overview

This project implements a custom 3D graphics engine designed for real-time rendering and interactive applications. The engine provides a flexible framework for building 3D games and simulations with support for physics, lighting, shadows, model loading, and custom shader pipelines.

## Architecture

### Core Design Patterns

**Entity-Component-System (ECS)**
- Decoupled architecture separating data (Components) from behavior (Systems)
- Entities act as containers for Components, enabling flexible object composition
- Component types: Mesh, Rigidbody, Camera, Light, Model
- EntityManager coordinates component lifecycle and inter-system communication

**Rendering Pipeline**
- Forward rendering with shadow mapping
- Depth texture generation for dynamic shadows
- Multi-pass rendering: shadow pass → geometry pass
- Skybox rendering with cube mapping
- Support for both solid colors and texture-based materials

**Physics Integration**
- Bullet Physics integration for rigid body dynamics
- Collision detection and response
- Configurable mass and dynamic/static body types
- Transform synchronization between physics and rendering systems

## Technical Features

### Graphics
- **OpenGL 3.3+ Core Profile** via GLAD loader
- **GLSL Shader System** with custom shader abstraction
- **Shadow Mapping** with configurable light projection
- **Skybox Rendering** using cube maps
- **Texture Support**: 2D textures and cube maps
- **Material System**: Ambient, diffuse, specular properties with shininess
- **Lighting**: Directional lights and point lights with distance-based attenuation

### Physics
- **Bullet Physics 3** integration
- Rigid body dynamics simulation
- Collision shapes matching visual geometry
- Support for static and dynamic objects
- Character controller capabilities

### Scene Management
- Object hierarchy and transforms (position, rotation, scale)
- Camera system with FPS-style controls
- Input handling via GLFW
- Debug UI powered by ImGui
- Multi-camera support

### Asset Loading
- **Assimp** integration for 3D model import
- Support for common formats (OBJ, FBX, etc.)
- Texture loading with STB Image
- Automatic mesh generation from model data

## System Requirements

### Dependencies
- **CMake 3.0+** - Build system
- **C++14** compiler (MSVC, GCC, or Clang)
- **OpenGL 3.3+** compatible graphics card

### Third-Party Libraries (Included)
- **GLFW** - Window and input management
- **GLAD** - OpenGL function loader
- **GLM** - Mathematics library
- **Assimp** - 3D model loading
- **Bullet3** - Physics engine
- **ImGui** - Debug interface
- **STB Image** - Image loading

## Building the Project

### Windows (Visual Studio)

```powershell
# Generate Visual Studio solution
cmake -B build -G "Visual Studio 16 2019"

# Build the project
cmake --build build --config Release
```

### Linux/macOS

```bash
# Generate makefiles
cmake -B build

# Build the project
cmake --build build
```

## Example Applications

The project includes several demonstration applications showcasing different engine capabilities:

### SimpleCube
Demonstrates basic rendering, lighting, texturing, and camera controls.
- Multiple geometric primitives (cubes, squares)
- Point and directional lighting
- Texture mapping and skybox rendering
- Free-look camera with keyboard/mouse input

### RigidBody
Physics simulation with multiple falling cubes.
- Rigid body dynamics
- Collision detection
- Static ground plane
- Transform synchronization

### LoadModel
3D model loading and rendering.
- Assimp integration
- Complex mesh rendering
- Material properties

### CharacterController
First-person character movement with physics.
- Kinematic character controller
- Collision response
- Camera attachment

### 2D
2D rendering capabilities within the 3D engine.

## Code Structure

```
3D-graphics-engine/
├── include/        # Public API headers
│   ├── ECS/              # Component system
│   └── utils/            # Utility functions
├── src/           # Engine implementation
├── examples/             # Sample applications
├── shaders/              # GLSL shader programs
├── textures/             # Sample textures
└── thirdparty/           # External dependencies
```

## Key Classes

### Engine
Main engine class inheriting from `EntityManager`. Manages the game loop, rendering, physics updates, and object lifecycle.

### Renderer
Handles all OpenGL rendering operations, shader management, shadow mapping, and framebuffer configuration.

### Object3D
Scene graph node representing any object in 3D space. Inherits from `Entity` to support component attachment.

### Component System
- `Mesh`: Geometric data and rendering properties
- `Rigidbody`: Physics simulation properties
- `Camera`: View and projection matrices
- `Light`: Lighting parameters (Point/Directional)
- `Model`: 3D model loaded from file

## Performance Characteristics

- **Delta-time based updates** for frame-rate independent simulation
- **Instanced rendering support** for efficient batch rendering
- **Depth pre-pass** for shadow optimization
- **Component caching** to minimize lookups

## Design Decisions

### Component-Based Architecture
The ECS pattern was chosen to maximize code reusability and flexibility. Objects are composed of orthogonal components rather than rigid class hierarchies, enabling easier feature combination and modification.

### Bullet Physics Integration
Bullet was selected for its maturity, performance, and comprehensive feature set. The integration maintains separation between rendering and simulation through transform synchronization.

### Forward Rendering
Despite being less scalable than deferred rendering for many lights, forward rendering was chosen for its simplicity and effectiveness for the target use cases (small to medium scenes with limited light sources).

## Future Enhancements

Potential areas for expansion:
- Deferred rendering pipeline for improved lighting scalability
- Post-processing effects (bloom, HDR, SSAO)
- Particle systems
- Skeletal animation support
- Audio system integration
- Scene serialization/deserialization
- Multi-threading for physics and rendering

## License

This project is licensed under the GNU General Public License v3.0 - see the LICENSE file for details.

## Technical Stack Summary

| Component | Technology |
|-----------|-----------|
| Language | C++14 |
| Graphics API | OpenGL 3.3+ |
| Windowing | GLFW 3.x |
| Math | GLM |
| Physics | Bullet Physics 3 |
| Model Loading | Assimp |
| UI | ImGui |
| Build System | CMake |

---

**Author Contact**: This project demonstrates professional software engineering practices including modern C++ design patterns, graphics programming, real-time simulation, and cross-platform development.