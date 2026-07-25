// Includes
#include "Engine.h"
#include "Object3D.h"

#include <iostream>

// Defines
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
            this->add_object(new Square(transform, GREY));

            transform.position = vec3(2, 0, 0);
            this->add_object(new Square(transform, GREY));

            transform.position = vec3(-2, 0, 0);
            this->add_object(new Square(transform, GREY));

            transform.position = vec3(0, 2, 0);
            this->add_object(new Square(transform, GREY));

            transform.position = vec3(0, -2, 0);
            this->add_object(new Square(transform, GREY));
        }

        /* update
         */
        void update() {

        }
};

/* main
 */
int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    Game game;

    if (!game.init()) {
        std::cerr << "Game Engine failed to initialize" << std::endl;
        return -1;
    }

    game.start();
    game.cleanup();

    return 0;
}