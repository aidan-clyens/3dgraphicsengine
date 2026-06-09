// Includes
#include "Engine.h"
#include "CubeMesh.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Mesh.h"
#include "Rigidbody.h"
#include "DynamicCharacterController.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define WHITE vec3(1, 1, 1)
#define GREY vec3(0.5, 0.5, 0.5)
#define DARK_GREY vec3(0.2, 0.2, 0.2)
#define ORANGE vec3(1, 0.5, 0.31)

// Class definitions
/* Game
 */
class Game : public Engine {
    public:
        /* process_keyboard_input
         */
        void process_keyboard_input() {
            const float speed = 80.0 * m_delta_time;
            DynamicCharacterController *controller = (DynamicCharacterController*) p_player->get_component(COMP_RIGIDBODY);

            vec2 front = vec2(p_camera->front().x, p_camera->front().z);
            vec2 right = vec2(p_camera->right().x, p_camera->right().z);
            vec2 player_direction = vec2(0, 0);

            if (p_input_manager->get_key(KEY_W) == KEY_PRESS) {
                player_direction += front * speed;
            }
            else if (p_input_manager->get_key(KEY_S) == KEY_PRESS) {
                player_direction += front * -speed;
            }

            if (p_input_manager->get_key(KEY_A) == KEY_PRESS) {
                player_direction += right * -speed;
            }
            else if (p_input_manager->get_key(KEY_D) == KEY_PRESS) {
                player_direction += right * speed;
            }

            if (p_input_manager->get_key(KEY_SPACE) == KEY_PRESS) {
                controller->jump();
            }

            if (p_input_manager->get_key(KEY_ESCAPE) == KEY_PRESS) {
                m_running = false;
            }

            controller->move(player_direction);
        }

        /* setup
         */
        void setup() {
            vec3 player_pos = vec3(0, 5, 0);

            p_camera->set_position(player_pos);
            this->set_mouse_visible(false);

            // Configure lighting
            m_material.ambient = GREY;
            m_material.diffuse = GREY;
            m_material.specular = WHITE;
            m_material.shininess = 4;

            // Create ground
            p_ground = new Object3D(vec3(0, 0, 0), vec3(0, 0, 0), vec3(50, 1, 50));
            p_ground->add_component(COMP_MESH, new CubeMesh());
            p_ground->add_component(COMP_RIGIDBODY, new Rigidbody(p_ground, 0));

            Transform transform = p_ground->get_transform();
            CubeMesh *mesh = (CubeMesh*)p_ground->get_component(COMP_MESH);

            mesh->set_material(m_material);
            mesh->set_transform(transform);

            this->add_object(p_ground);

            // Create obstacles
            p_wall1 = new Object3D(vec3(0, 1, -8), vec3(0, 0, 0), vec3(8, 1, 1));
            p_wall1->add_component(COMP_MESH, new CubeMesh());
            p_wall1->add_component(COMP_RIGIDBODY, new Rigidbody(p_wall1, 0));

            transform = p_wall1->get_transform();
            mesh = (CubeMesh*)p_wall1->get_component(COMP_MESH);

            m_material.ambient = DARK_GREY;
            m_material.diffuse = DARK_GREY;

            mesh->set_material(m_material);
            mesh->set_transform(transform);

            this->add_object(p_wall1);

            p_wall2 = new Object3D(vec3(4, 1, -8), vec3(0, 0, 0), vec3(1, 1, 8));
            p_wall2->add_component(COMP_MESH, new CubeMesh());
            p_wall2->add_component(COMP_RIGIDBODY, new Rigidbody(p_wall2, 0));

            transform = p_wall2->get_transform();
            mesh = (CubeMesh*)p_wall2->get_component(COMP_MESH);

            mesh->set_material(m_material);
            mesh->set_transform(transform);

            this->add_object(p_wall2);

            // Create character controller
            p_player = new Object3D(player_pos, vec3(0, 0, 0), vec3(1, 2, 1));
            p_player->add_component(COMP_RIGIDBODY, new DynamicCharacterController(p_player, 1));
            p_player->add_component(COMP_CAMERA, p_camera);

            this->add_object(p_player);
        }

        /* update
         */
        void update() {
            this->process_keyboard_input();

            p_camera->set_position(p_player->get_transform().position);

            if (p_input_manager->is_mouse_updated()) {
                vec2 mouse_pos = p_input_manager->get_mouse_position();

                p_camera->set_mouse_offset(mouse_pos.x, mouse_pos.y);
                p_input_manager->set_mouse_handled(true);
            }
        }

    private:
        Object3D *p_ground;
        Object3D *p_wall1;
        Object3D *p_wall2;
        Object3D *p_player;

        Material m_material;
};

/* main
 */
int main(int argc, char **argv) {
    Game game;

    if (!game.init()) {
        std::cerr << "Game Engine failed to initialize" << std::endl;
        return -1;
    }

    game.start();
    game.cleanup();

    return 0;
}