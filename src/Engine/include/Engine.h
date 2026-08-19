#pragma once

// Includes
#include "Types.h"
#include "ECS.h"
#include "Mesh.h"
#include "Model.h"
#include "Renderer.h"
#include "Object3D.h"
#include "Camera.h"
#include "InputManager.h"
#ifdef BUILD_BULLET3
#include "Physics.h"
#endif
#include "Light.h"
#include "DebugWindow.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

// Structs
typedef struct
{
    vec2 min;
    vec2 max;
} WorldBounds;

/* Engine
 */
class Engine : public EntityManager
{
public:
    // Engine();
    Engine(int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT, const std::string &path = "");
    virtual ~Engine();

    bool init();
    void start();
    void cleanup();

    void add_object(Object3D *object);
    void remove_object(Object3D *object);
    void get_objects(std::vector<Object3D *> &objects);

    Object3D *create_model(Transform transform, const std::string &path);

    void set_directional_light(DirectionalLight light);
    DirectionalLight get_directional_light() const;

    void set_background_color(vec3 color);
    void set_skybox(Object3D *skybox);

    void set_camera(Camera *camera);
    void get_cameras(std::vector<Camera *> &cameras);
    Camera *get_camera();

    void set_mouse_visible(bool value);

    void set_shadows_enabled(bool enable);

    void enable_debug_window();
    void disable_debug_window();

    double get_delta_time() const;

    vec2 get_screen_dimensions() const;

    WorldBounds get_world_boundaries() const;

    // To be implemented by user
    virtual void setup() = 0;
    virtual void update() = 0;

    void process_mouse_button(int button, int action, int mods);
    void process_mouse_input(double x, double y);

    GLFWwindow *get_window();

    LightingInfo get_lighting_info() const;
    void set_lighting_info(LightingInfo info);

    void handle_add_component(Entity *entity, eComponentType type);
    void handle_remove_component(Entity *entity, eComponentType type);

protected:
    InputManager *p_input_manager;
#ifdef BUILD_BULLET3
    Physics m_physics;
#endif

    Camera *p_camera;

    double m_delta_time;
    bool m_running;

private:
    void static _process_mouse_button(GLFWwindow *window, int button, int action, int mods);
    void static _process_mouse_input(GLFWwindow *window, double x, double y);

    Renderer m_renderer;

    std::vector<Camera *> m_cameras;
    std::vector<Object3D *> m_objects;
    std::vector<Mesh *> m_meshes;
    std::vector<Light *> m_lights;
};