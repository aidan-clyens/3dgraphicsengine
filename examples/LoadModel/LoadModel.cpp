// Includes
#include "Engine.h"
#include "Shader.h"
#include "TextureCubeMap.h"
#include "Light.h"
#include "Timer.h"
#include "Cube.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define GREY vec3(0.4, 0.4, 0.4)
#define ORANGE vec3(1, 0.5, 0.31)
#define BLUE vec3(0, 0.28, 1)
#define SKY_BLUE vec3(0.529, 0.808, 0.922)

static bool key_ready = true;

// Class definitions
/* Game
 */
class Game : public Engine
{
public:
    /* process_mouse_input
     */
    void process_keyboard_input()
    {
        const float speed = 2.5 * m_delta_time;

        if (!m_mouse_enabled)
        {
            if (p_input_manager->get_key(KEY_W) == KEY_PRESS)
            {
                p_camera->translate_x(speed);
            }
            if (p_input_manager->get_key(KEY_S) == KEY_PRESS)
            {
                p_camera->translate_x(-speed);
            }
            if (p_input_manager->get_key(KEY_A) == KEY_PRESS)
            {
                p_camera->translate_z(-speed);
            }
            if (p_input_manager->get_key(KEY_D) == KEY_PRESS)
            {
                p_camera->translate_z(speed);
            }
            if (p_input_manager->get_key(KEY_SPACE) == KEY_PRESS)
            {
                p_camera->translate_y(speed);
            }
            if (p_input_manager->get_key(KEY_LEFT_SHIFT) == KEY_PRESS)
            {
                p_camera->translate_y(-speed);
            }
        }

        if (p_input_manager->get_key(KEY_ESCAPE) == KEY_PRESS)
        {
            if (key_ready)
            {
                m_mouse_enabled = !m_mouse_enabled;
                m_debug_window_enabled = !m_debug_window_enabled;
                this->set_mouse_visible(m_mouse_enabled);

                if (m_debug_window_enabled)
                {
                    this->enable_debug_window();
                }
                else
                {
                    this->disable_debug_window();
                }

                Timer([]()
                      { key_ready = true; }, 100);
            }
        }
    }

    /* setup
     */
    void setup()
    {
        m_mouse_enabled = false;
        m_debug_window_enabled = false;

        this->disable_debug_window();
        this->set_mouse_visible(m_mouse_enabled);
        this->set_shadows_enabled(true);

        // Load skybox texture
        std::vector<std::string> skybox_faces;
        skybox_faces.push_back("examples/SimpleCube/res/skybox/right.jpg");
        skybox_faces.push_back("examples/SimpleCube/res/skybox/left.jpg");
        skybox_faces.push_back("examples/SimpleCube/res/skybox/top.jpg");
        skybox_faces.push_back("examples/SimpleCube/res/skybox/bottom.jpg");
        skybox_faces.push_back("examples/SimpleCube/res/skybox/front.jpg");
        skybox_faces.push_back("examples/SimpleCube/res/skybox/back.jpg");
        m_skybox_texture.load(skybox_faces);

        // Ground
        Transform transform;
        transform.position = vec3(0, -2, 0);
        transform.rotation = vec3(0, 0, 0);
        transform.size = vec3(50, 1, 50);

        Object3D *object = new Cube(transform, GREY, 4);
        object->set_name("Ground");
        this->add_object(object);

        // Skybox
        this->set_skybox(new Cube(Transform(), m_skybox_texture));

        // Model
        transform.position = vec3(0, 0, 0);
        transform.rotation = vec3(-90, 0, -90);
        transform.size = vec3(1, 1, 1);

        object = this->create_model(transform, "examples/LoadModel/res/suzanne.fbx");
        object->set_name("Model");
        this->add_object(object);
    }

    /* update
     */
    void update()
    {
        this->process_keyboard_input();

        if (!m_mouse_enabled)
        {
            if (p_input_manager->is_mouse_updated())
            {
                vec2 mouse_pos = p_input_manager->get_mouse_position();

                p_camera->set_mouse_offset(mouse_pos.x, mouse_pos.y);
                p_input_manager->set_mouse_handled(true);
            }
        }
    }

private:
    TextureCubeMap m_skybox_texture;

    bool m_mouse_enabled;
    bool m_debug_window_enabled;
};

/* main
 */
int main(int argc, char **argv)
{
    (void)argc; // Unused
    (void)argv; // Unused

    Game game;

    if (!game.init())
    {
        std::cerr << "Game Engine failed to initialize" << std::endl;
        return -1;
    }

    game.start();
    game.cleanup();

    return 0;
}