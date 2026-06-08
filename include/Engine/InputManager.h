#pragma once

// Includes
#include "Types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>

// Defines
#define MOUSE_SENSITIVITY 0.1

// Enums
/* eKey
 */
typedef enum {
    KEY_W           = GLFW_KEY_W,
    KEY_S           = GLFW_KEY_S,
    KEY_A           = GLFW_KEY_A,
    KEY_D           = GLFW_KEY_D,
    KEY_SPACE       = GLFW_KEY_SPACE,
    KEY_LEFT_SHIFT  = GLFW_KEY_LEFT_SHIFT,
    KEY_ESCAPE      = GLFW_KEY_ESCAPE,
    KEY_TAB         = GLFW_KEY_TAB,
    KEY_NOT_IMPLEMENTED
} eKey;

/* eKeyAction
 */
typedef enum {
    KEY_PRESS       = GLFW_PRESS,
    KEY_REPEAT      = GLFW_REPEAT,
    KEY_RELEASE     = GLFW_RELEASE
} eKeyAction;


class InputManager {
    public:
        static InputManager *get_instance();

        void set_render_window(GLFWwindow *window);
        void set_screen_dimensions(int width, int height);

        eKeyAction get_key(eKey key);
        void process_mouse_input(double x, double y);

        vec2 get_mouse_position() const;

        bool is_mouse_updated() const;
        void set_mouse_handled(bool value);

    private:
        InputManager();

        static InputManager *p_instance;

        GLFWwindow *p_window;

        int m_screen_width;
        int m_screen_height;

        // Mouse
        bool m_first_mouse;
        double m_last_mouse_pos_x;
        double m_last_mouse_pos_y;
        double m_mouse_offset_x;
        double m_mouse_offset_y;
        bool m_mouse_updated;
};