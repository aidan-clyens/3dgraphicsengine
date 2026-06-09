// Includes
#include "Engine.h"
#include "CubeMesh.h"
#include "Shader.h"
#include "Texture2D.h"
#include "Mesh.h"
#include "Rigidbody.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define WHITE vec3(1, 1, 1)
#define GREY vec3(0.5, 0.5, 0.5)
#define ORANGE vec3(1, 0.5, 0.31)

// Class definitions
/* Game
 */
class Game : public Engine {
    public:
        /* setup
         */
        void setup() {
            p_camera->set_position(vec3(0, 0, 3));
            // this->set_mouse_visible(false);

            // Configure lighting
            m_material.ambient = GREY;
            m_material.diffuse = GREY;
            m_material.specular = WHITE;
            m_material.shininess = 4;

            // Create ground
            p_ground = new Object3D(vec3(0, -2, 0), vec3(0, 0, 0), vec3(50, 1, 50));
            p_ground->add_component(COMP_MESH, new CubeMesh());
            p_ground->add_component(COMP_RIGIDBODY, new Rigidbody(p_ground, 0));

            Transform transform = p_ground->get_transform();
            CubeMesh *mesh = (CubeMesh*)p_ground->get_component(COMP_MESH);

            mesh->set_material(m_material);
            mesh->set_transform(transform);

            this->add_object(p_ground);

            // Create cubes
            for (int i = 0; i < 4; i++) {
                m_cubes.push_back(new Object3D(vec3((2*i - 3), 2*i, -5), vec3(0, 30, 0), vec3(1, 1, 1)));
                m_cubes[i]->add_component(COMP_MESH, new CubeMesh());
                m_cubes[i]->add_component(COMP_RIGIDBODY, new Rigidbody(m_cubes[i], 1));

                Mesh *cube_mesh = (CubeMesh*)m_cubes[i]->get_component(COMP_MESH);
                transform = m_cubes[i]->get_transform();

                m_material.ambient = ORANGE;
                m_material.diffuse = ORANGE;

                cube_mesh->set_material(m_material);
                cube_mesh->set_transform(transform);

                this->add_object(m_cubes[i]);
            }
        }

        /* update
         */
        void update() {

        }
    
    private:
        Object3D *p_ground;

        std::vector<Object3D*> m_cubes;

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