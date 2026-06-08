#include "Engine/InputManager.h"


InputManager *InputManager::p_instance = 0;

/* InputManager
 */
InputManager::InputManager():
m_first_mouse(false),
m_mouse_offset_x(0),
m_mouse_offset_y(0),
m_mouse_updated(false)
{

}

/* get_instance
 */
InputManager *InputManager::get_instance() {
    if (p_instance == 0) {
        p_instance = new InputManager();
    }

    return p_instance;
}

/* set_render_window
 */
void InputManager::set_render_window(GLFWwindow *window) {
    p_window = window;
}

/* set_screen_dimensions
 */
void InputManager::set_screen_dimensions(int width, int height) {
    m_screen_width = width;
    m_screen_height = height;

    m_last_mouse_pos_x = width / 2;
    m_last_mouse_pos_y = height / 2;
}

/* get_key
 */
eKeyAction InputManager::get_key(eKey key) {
    return (eKeyAction)glfwGetKey(p_window, key);
}

/* process_mouse_input
 */
void InputManager::process_mouse_input(double x, double y) {
    if (m_first_mouse) {
        m_last_mouse_pos_x = x;
        m_last_mouse_pos_y = y;
        m_first_mouse = false;
    }

    m_mouse_offset_x = x - m_last_mouse_pos_x;
    m_mouse_offset_y = m_last_mouse_pos_y - y;

    m_last_mouse_pos_x = x;
    m_last_mouse_pos_y = y;

    m_mouse_offset_x *= MOUSE_SENSITIVITY;
    m_mouse_offset_y *= MOUSE_SENSITIVITY;

    m_mouse_updated = true;
}

/* get_mouse_position
 */
vec2 InputManager::get_mouse_position() const {
    return vec2(m_mouse_offset_x, m_mouse_offset_y);
}

/* is_mouse_updated
 */
bool InputManager::is_mouse_updated() const {
    return m_mouse_updated;
}

/* set_mouse_handled
 */
void InputManager::set_mouse_handled(bool value) {
    m_mouse_updated = !value;
}