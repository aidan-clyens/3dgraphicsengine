// Includes
#include "Engine.h"
#include "SquareMesh.h"
#include "Object3D.h"

#include <iostream>

// Defines
#define WHITE vec3(1, 1, 1)
#define GREY vec3(0.6, 0.6, 0.6)

// Class definitions
/* Game
 */
class Game : public Engine {
    public:
        /* setup
         */
        void setup() {
            this->set_mouse_visible(true);
            this->set_debug_window_enabled(false);
            this->set_shadows_enabled(false);

            p_camera->set_position(vec3(0, 0, 10));

            // Square
            Transform transform;
            transform.rotation = vec3(0, 0, 0);
            transform.size = vec3(1, 1, 1);

            transform.position = vec3(0, 0, 0);
            this->add_object(this->create_square(transform, GREY));

            transform.position = vec3(2, 0, 0);
            this->add_object(this->create_square(transform, GREY));

            transform.position = vec3(-2, 0, 0);
            this->add_object(this->create_square(transform, GREY));

            transform.position = vec3(0, 2, 0);
            this->add_object(this->create_square(transform, GREY));

            transform.position = vec3(0, -2, 0);
            this->add_object(this->create_square(transform, GREY));
        }

        /* update
         */
        void update() {

        }

        /* create_square
         */
        Object3D *create_square(Transform transform, vec3 color) {
            // Configure material
            Material material;
            material.specular = WHITE;
            material.ambient = color;
            material.diffuse = color;
            material.shininess = 1;

            // Create object
            Object3D *square = new Object3D(transform.position, transform.rotation, transform.size);
            square->add_component(COMP_MESH, new SquareMesh());

            SquareMesh *mesh = (SquareMesh *)square->get_component(COMP_MESH);

            mesh->set_material(material);
            mesh->set_transform(transform);

            return square;
        }
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