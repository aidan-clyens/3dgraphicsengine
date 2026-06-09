#pragma once

// Includes
#include "Types.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"


class Engine;
class Object3D;
class Mesh;
class Model;
class Light;
class Texture;
class Camera;


class DebugWindow {
    public:
        static void init(Engine *engine);
        static void close();

        static void create_window();
        static void render();
        static void render_draw_data();

        static void add_mouse_button_event(int button, int action);

        static bool want_capture_mouse();

    private:
        static void show_window(bool *open);

        static void show_scene();
        static void show_cameras();

        static void show_objects();
        static void show_transform(Object3D *object);
        static void show_components(Object3D *object);
        static void show_model(Model *model);
        static void show_mesh(Mesh *mesh);
        static void show_light(Light *light);
        static void show_camera(Camera *camera);
        static void show_debug();

        static float show_float(const float value, float step = 0.01f, float min = NULL, float max = NULL);
        static vec3 show_vec3(const vec3 vector, float step = 0.01f, float min = NULL, float max = NULL);
        static vec3 show_color3(const vec3 color, ImGuiColorEditFlags flags = 0);
        static void show_image(const Texture texture);

        static Engine *p_engine;
};