#pragma once

// Includes
#include "Types.h"
#include "ECS.h"
#include "Mesh.h"
#include "Model.h"
#include "Engine/Renderer.h"
#include "Engine/Object3D.h"
#include "Engine/Camera.h"
#include "Engine/InputManager.h"
#include "Engine/Physics.h"
#include "Engine/Light.h"
#include "Engine/DebugWindow.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

/* Engine
 */
class Engine : public EntityManager {
    public:
        // Engine();
        Engine(int width=SCREEN_WIDTH, int height=SCREEN_HEIGHT, const std::string &path="");
        virtual ~Engine();

        bool init();
        void start();
        void cleanup();

        void add_object(Object3D *object);
        void remove_object(Object3D *object);
        void get_objects(std::vector<Object3D*> &objects);

        void set_directional_light(DirectionalLight light);
        DirectionalLight get_directional_light() const;

        void set_background_color(vec3 color);
        void set_skybox(Object3D *skybox);

        void set_camera(Camera *camera);
        void get_cameras(std::vector<Camera*> &cameras);
        Camera *get_camera();

        void set_mouse_visible(bool value);

        void set_shadows_enabled(bool enable);

        void set_debug_window_enabled(bool enable);

        // To be implemented by user
        virtual void setup();
        virtual void update();

        void process_mouse_button(int button, int action, int mods);
        void process_mouse_input(double x, double y);

        Renderer *get_renderer();

        void handle_add_component(Entity *entity, Component *component, eComponentType type);
        void handle_remove_component(Entity *entity, Component *component, eComponentType type);

    protected:
        InputManager *p_input_manager;
        Physics m_physics;

        Camera *p_camera;

        double m_delta_time;
        bool m_running;

    private:
        void static _process_mouse_button(GLFWwindow *window, int button, int action, int mods);
        void static _process_mouse_input(GLFWwindow *window, double x, double y);

        Renderer m_renderer;

        std::vector<Camera*> m_cameras;
        std::vector<Object3D*> m_objects;
        std::vector<Mesh*> m_meshes;
        std::vector<Light*> m_lights;
};