#pragma once

// Includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>
#include <vector>

#include "Engine/utils/types.h"
#include "Engine/Shader.h"
#include "Engine/DepthTexture.h"
#include "Engine/Light.h"
#include "Engine/Object3D.h"

// Forward declarations
class Engine;
class Mesh;
class Camera;

// Structs
typedef struct {
    float light_projection_size;
    float near_plane;
    float far_plane;
} LightingInfo;

/* Renderer
 */
class Renderer {
    public:
        Renderer(int width, int height, const std::string &path);

        bool init(Engine *engine);
        void close();

        void render(std::vector<Mesh*> &meshes, std::vector<Light*> &lights, Camera &camera);

        bool is_window_closed() const;

        void set_key_callback(GLFWkeyfun callback);
        void set_mouse_button_callback(GLFWmousebuttonfun callback);
        void set_mouse_callback(GLFWcursorposfun callback);

        void set_mouse_visible(bool value);

        void set_directional_light(DirectionalLight light);
        DirectionalLight get_directional_light() const;

        void set_background_color(vec3 color);
        void set_skybox(Object3D *skybox);

        void set_shadows_enabled(bool enable);

        void set_debug_window_enabled(bool enable);

        LightingInfo get_lighting_info() const;
        void set_lighting_info(LightingInfo info);

        GLFWwindow *get_window();

        vec2 get_screen_size() const { return vec2(m_width, m_height); }

    private:
        void on_key_pressed(GLFWwindow *p_window, int key, int scancode, int action, int mods);

        // Debug
        void render_debug_quad();

        int m_width;
        int m_height;
        GLFWwindow *p_window;

        std::string m_path;

        mat4 m_model;
        mat4 m_view;
        mat4 m_projection;

        // Frame buffer objects
        unsigned int m_depth_map_buffer_object;

        // Shader
        Shader m_object_shader;
        Shader m_skybox_shader;

        // Depth map
        Shader m_depth_shader;
        Shader m_debug_depth_shader;
        DepthTexture m_depth_texture;

        // Lighting
        DirectionalLight m_directional_light;
        std::vector<PointLight> m_lights;

        LightingInfo m_lighting_info;

        // Skybox
        Object3D *p_skybox;

        vec3 m_background_color;

        bool m_enable_shadows;
        bool m_enable_debug_window;

        // Debug
        unsigned int m_debug_quad_array_object;
        unsigned int m_debug_quad_buffer_object;
};