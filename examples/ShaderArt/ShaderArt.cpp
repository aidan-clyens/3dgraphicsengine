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
        // Game(): Engine(900, 900) {}

        /* setup
         */
        void setup() {
            this->set_mouse_visible(true);
            this->set_debug_window_enabled(false);
            this->set_shadows_enabled(false);

            m_shader.load("examples/ShaderArt/shaders/background_vertex.glsl", "examples/ShaderArt/shaders/background_fragment.glsl");

            if (!m_shader.is_valid()) {
                std::cerr << "Shader failed to load" << std::endl;
            }

            // Background
            Transform transform;
            transform.rotation = vec3(0, 0, 0);
            transform.size = vec3(1, 1, 1);
            transform.position = vec3(0, 0, 0);

            this->add_object(this->create_square(transform, m_shader));
        }

        /* update
         */
        void update() {

        }

        /* create_square
         */
        Object3D *create_square(Transform transform, Shader &shader) {
            // Create object
            Object3D *square = new Object3D(transform.position, transform.rotation, transform.size);
            square->add_component(COMP_MESH, new SquareMesh());

            SquareMesh *mesh = (SquareMesh *)square->get_component(COMP_MESH);

            mesh->set_shader(shader);
            mesh->set_transform(transform);

            return square;
        }
    
    private:
        Shader m_shader;
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