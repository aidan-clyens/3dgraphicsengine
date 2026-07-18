// Includes
#include "Engine.h"
#include "SquareMesh.h"
#include "CubeMesh.h"
#include "Shader.h"
#include "Texture2D.h"
#include "TextureCubeMap.h"
#include "Light.h"
#include "Mesh.h"
#include "Timer.h"
#include "Logger.h"

#include <iostream>

// Defines
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define WHITE vec3(1, 1, 1)
#define GREY vec3(0.4, 0.4, 0.4)
#define ORANGE vec3(1, 0.5, 0.31)
#define BLUE vec3(0, 0.28, 1)
#define SKY_BLUE vec3(0.529, 0.808, 0.922)

static bool key_ready = true;

constexpr const char *APP_LOG_FILEPATH = "SimpleCube.log";

// Class definitions
/* Game
 */
class Game : public Engine {
    public:

        Game() {
            // Setup logging
            Logger::instance().enable_console_output(true);
            Logger::instance().set_log_file(APP_LOG_FILEPATH);
            set_thread_name("Main");
        }

        /* process_mouse_input
         */
        void process_keyboard_input() {
            const float speed = 2.5 * m_delta_time;

            if (!m_mouse_enabled) {
                if (p_input_manager->get_key(KEY_W) == KEY_PRESS) {
                    p_camera->translate_x(speed);
                }
                if (p_input_manager->get_key(KEY_S) == KEY_PRESS) {
                    p_camera->translate_x(-speed);
                }
                if (p_input_manager->get_key(KEY_A) == KEY_PRESS) {
                    p_camera->translate_z(-speed);
                }
                if (p_input_manager->get_key(KEY_D) == KEY_PRESS) {
                    p_camera->translate_z(speed);
                }
                if (p_input_manager->get_key(KEY_SPACE) == KEY_PRESS) {
                    p_camera->translate_y(speed);
                }
                if (p_input_manager->get_key(KEY_LEFT_SHIFT) == KEY_PRESS) {
                    p_camera->translate_y(-speed);
                }
            }

            if (p_input_manager->get_key(KEY_ESCAPE) == KEY_PRESS) {
                if (key_ready) {
                    m_mouse_enabled = !m_mouse_enabled;
                    m_debug_window_enabled = !m_debug_window_enabled;
                    this->set_mouse_visible(m_mouse_enabled);
                    this->set_debug_window_enabled(m_debug_window_enabled);
                    Timer([]() { key_ready = true; }, 100);
                }
            }
        }

        /* setup
         */
        void setup() {
            m_mouse_enabled = false;
            m_debug_window_enabled = false;

            this->set_mouse_visible(m_mouse_enabled);
            this->set_debug_window_enabled(m_debug_window_enabled);
            this->set_shadows_enabled(true);
            this->set_background_color(SKY_BLUE);

            // Load textures
            m_texture_2d.load("examples/SimpleCube/res/brick.png");

            std::vector<std::string> faces;
            for (int i = 0; i < 6; i++) {
                faces.push_back("examples/SimpleCube/res/brick.png");
            }
            m_texture_cube.load(faces);

            // Load skybox texture
            std::vector<std::string> skybox_faces;
            skybox_faces.push_back("examples/SimpleCube/res/skybox/right.jpg");
            skybox_faces.push_back("examples/SimpleCube/res/skybox/left.jpg");
            skybox_faces.push_back("examples/SimpleCube/res/skybox/top.jpg");
            skybox_faces.push_back("examples/SimpleCube/res/skybox/bottom.jpg");
            skybox_faces.push_back("examples/SimpleCube/res/skybox/front.jpg");
            skybox_faces.push_back("examples/SimpleCube/res/skybox/back.jpg");
            m_skybox_texture.load(skybox_faces);

            // Camera
            Object3D *camera = this->create_camera(vec3(0, 0, 3));
            camera->set_name("Camera");
            this->add_object(camera);
            this->set_camera((Camera*)camera->get_component(COMP_CAMERA));

            // Ground
            Transform transform;
            transform.position = vec3(0, -2, 0);
            transform.rotation = vec3(0, 0, 0);
            transform.size = vec3(20, 1, 20);

            Object3D *object = this->create_cube(transform, GREY, 4);
            object->set_name("Ground");
            this->add_object(object);

            // Skybox
            this->set_skybox(this->create_cube(Transform(), m_skybox_texture));

            // Cube 1
            transform.position = vec3(0, -1, -3);
            transform.rotation = vec3(0, 30, 0);
            transform.size = vec3(1, 1, 1);

            object = this->create_cube(transform, m_texture_cube);
            object->set_name("Cube 1");
            this->add_object(object);

            // Cube 2
            transform.position = vec3(2, -1, -4);
            transform.rotation = vec3(0, -10, 0);
            transform.size = vec3(1, 4, 1);

            object = this->create_cube(transform, BLUE, 4);
            object->set_name("Cube 2");
            this->add_object(object);

            // Square
            transform.position = vec3(0, 0, -4);
            transform.rotation = vec3(0, 0, 0);
            transform.size = vec3(1, 1, 1);

            object = this->create_square(transform, m_texture_2d);
            object->set_name("Square");
            this->add_object(object);

            // Lights
            object = this->create_point_light(vec3(-1.0, 0.0, 2.0), vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), vec3(0.2, 0.2, 0.2), LIGHT_DISTANCE_32);
            object->set_name("Point Light 1");
            this->add_object(object);

            object = this->create_point_light(vec3(5.0, 0.0, -5.0), vec3(0.5, 0.5, 0.5), vec3(0.5, 0.5, 0.5), vec3(0.2, 0.2, 0.2), LIGHT_DISTANCE_7);
            object->set_name("Point Light 2");
            this->add_object(object);
        }

        /* update
         */
        void update() {
            this->process_keyboard_input();

            if (!m_mouse_enabled) {
                if (p_input_manager->is_mouse_updated()) {
                    vec2 mouse_pos = p_input_manager->get_mouse_position();

                    p_camera->set_mouse_offset(mouse_pos.x, mouse_pos.y);
                    p_input_manager->set_mouse_handled(true);
                }
            }
        }

        /* create_point_light
         */
        Object3D *create_point_light(vec3 position, vec3 ambient, vec3 diffuse, vec3 specular, ePointLightDistance strength) {
            // Create object
            Object3D *light_object = new Object3D(position, vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f));
            light_object->add_component(COMP_LIGHT, new PointLight());

            PointLight *light = (PointLight *)light_object->get_component(COMP_LIGHT);

            light->set_position(position);
            light->set_lighting(ambient, diffuse, specular);
            light->set_light_strength(strength);

            return light_object;
        }

        /* create_cube
         */
        Object3D *create_cube(Transform transform, vec3 color, int shininess) {
            // Configure material
            Material material;
            material.specular = WHITE;
            material.ambient = color;
            material.diffuse = color;
            material.shininess = shininess;

            // Create object
            Object3D *cube = new Object3D(transform.position, transform.rotation, transform.size);
            cube->add_component(COMP_MESH, new CubeMesh());

            CubeMesh *mesh = (CubeMesh *)cube->get_component(COMP_MESH);

            mesh->set_material(material);
            mesh->set_transform(transform);

            return cube;
        }

        /* create_cube
         */
        Object3D *create_cube(Transform transform, Texture texture) {
            // Create object
            Object3D *cube = new Object3D(transform.position, transform.rotation, transform.size);
            cube->add_component(COMP_MESH, new CubeMesh());

            CubeMesh *mesh = (CubeMesh *)cube->get_component(COMP_MESH);

            mesh->set_texture(texture);
            mesh->set_transform(transform);

            return cube;
        }

        /* create_square
         */
        Object3D *create_square(Transform transform, Texture texture) {
            // Create object
            Object3D *square = new Object3D(transform.position, transform.rotation, transform.size);
            square->add_component(COMP_MESH, new SquareMesh());

            SquareMesh *mesh = (SquareMesh *)square->get_component(COMP_MESH);

            mesh->set_texture(texture);
            mesh->set_transform(transform);

            return square;
        }

        /* create_camera
         */
        Object3D *create_camera(vec3 position) {
            Object3D *camera = new Object3D();
            camera->set_position(position);
            camera->add_component(COMP_CAMERA, new Camera(position));

            return camera;
        }

    private:
        Texture2D m_texture_2d;
        TextureCubeMap m_texture_cube;
        TextureCubeMap m_skybox_texture;

        bool m_mouse_enabled;
        bool m_debug_window_enabled;
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