#include "Engine.h"

#include "Clock.h"


/* Engine
 */
Engine::Engine(int width, int height, const std::string &path):
m_renderer(width, height, path),
p_camera(new Camera(vec3(0, 0, 0))),
p_input_manager(InputManager::get_instance())
{

}

/* ~Engine
 */
Engine::~Engine() {

}

/* init
 */
bool Engine::init() {
    if (!m_renderer.init(this)) {
        std::cerr << "Failed to init Renderer" << std::endl;
        m_renderer.close();
        return false;
    }

    glfwSetWindowUserPointer(m_renderer.get_window(), this);

    p_input_manager->set_render_window(m_renderer.get_window());
    p_input_manager->set_screen_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT);

    m_renderer.set_mouse_button_callback(this->_process_mouse_button);
    m_renderer.set_mouse_callback(this->_process_mouse_input);

    // Start clock
    Clock::instance()->init();

    return true;
}

/* start
 */
void Engine::start() {
    this->setup();

    // Main rendering loop
    double current_frame = 0;
    double last_frame = 0;
    m_running = true;
    while (!m_renderer.is_window_closed() && m_running) {
        current_frame = glfwGetTime();
        m_delta_time = current_frame - last_frame;
        last_frame = current_frame;

        this->update();

        m_physics.update(m_delta_time);
        m_renderer.render(m_meshes, m_lights, *p_camera);
    }
}

/* cleanup
 */
void Engine::cleanup() {
    for (Object3D *object : m_objects) {
        delete object;
    }

    m_physics.cleanup();
    m_renderer.close();
}

/* add_object
 */
void Engine::add_object(Object3D *object) {
    object->assign_entity_manager(this);
    m_objects.push_back(object);

    if (object->has_component(COMP_MESH)) {
        this->handle_add_component(object, object->get_component(COMP_MESH), COMP_MESH);
    }

    if (object->has_component(COMP_RIGIDBODY)) {
        this->handle_add_component(object, object->get_component(COMP_RIGIDBODY), COMP_RIGIDBODY);
    }

    if (object->has_component(COMP_CAMERA)) {
        this->handle_add_component(object, object->get_component(COMP_CAMERA), COMP_CAMERA);
    }

    if (object->has_component(COMP_LIGHT)) {
        this->handle_add_component(object, object->get_component(COMP_LIGHT), COMP_LIGHT);
    }

    if (object->has_component(COMP_MODEL)) {
        this->handle_add_component(object, object->get_component(COMP_MODEL), COMP_MODEL);
    }
}

/* remove_object
 */
void Engine::remove_object(Object3D *object) {
    // Remove components
    if (object->has_component(COMP_MESH)) {
        this->handle_remove_component(object, object->get_component(COMP_MESH), COMP_MESH);
    }

    if (object->has_component(COMP_RIGIDBODY)) {
        this->handle_remove_component(object, object->get_component(COMP_RIGIDBODY), COMP_RIGIDBODY);
    }

    if (object->has_component(COMP_CAMERA)) {
        this->handle_remove_component(object, object->get_component(COMP_CAMERA), COMP_CAMERA);
    }

    if (object->has_component(COMP_LIGHT)) {
        this->handle_remove_component(object, object->get_component(COMP_LIGHT), COMP_LIGHT);
    }

    if (object->has_component(COMP_MODEL)) {
        this->handle_remove_component(object, object->get_component(COMP_MODEL), COMP_MODEL);
    }

    // Remove object
    auto it = std::find(m_objects.begin(), m_objects.end(), object);
    if (it != m_objects.end()) {
        m_objects.erase(it);
    }

    delete object;
}

/* get_objects
 */
void Engine::get_objects(std::vector<Object3D *> &objects) {
    objects = m_objects;
}

/* set_directional_light
 */
void Engine::set_directional_light(DirectionalLight light) {
    m_renderer.set_directional_light(light);
}

/* get_directional_light
 */
DirectionalLight Engine::get_directional_light() const {
    return m_renderer.get_directional_light();
}

/* set_background_color
 */
void Engine::set_background_color(vec3 color) {
    m_renderer.set_background_color(color);
}

/* set_skybox
 */
void Engine::set_skybox(Object3D *skybox) {
    m_renderer.set_skybox(skybox);
}

/* set_camera
 */
void Engine::set_camera(Camera *camera) {
    p_camera = camera;
}

/* get_cameras
 */
void Engine::get_cameras(std::vector<Camera*> &cameras) {
    cameras = m_cameras;
}

/* get_camera
 */
Camera *Engine::get_camera() {
    return p_camera;
}

/* set_mouse_visible
 */
void Engine::set_mouse_visible(bool value) {
    m_renderer.set_mouse_visible(value);
}

/* set_shadows_enabled
 */
void Engine::set_shadows_enabled(bool enable) {
    m_renderer.set_shadows_enabled(enable);
}

/* set_debug_window_enabled
 */
void Engine::set_debug_window_enabled(bool enable) {
    m_renderer.set_debug_window_enabled(enable);
}

/* setup
 */
void Engine::setup() {

}

/* update
 */
void Engine::update() {

}

/* process_mouse_button
 */
void Engine::process_mouse_button(int button, int action, int mods) {
    DebugWindow::add_mouse_button_event(button, action);
}

/* process_mouse_input
 */
void Engine::process_mouse_input(double x, double y) {
    p_input_manager->process_mouse_input(x, y);
}

/* get_renderer
 */
Renderer *Engine::get_renderer() {
    return &m_renderer;
}

/* handle_add_component
 */
void Engine::handle_add_component(Entity *entity, Component *component, eComponentType type) {
    if (entity->has_component(type)) {
        switch (type) {
            case COMP_MESH: {
                Mesh *mesh = (Mesh*)entity->get_component(type);
                if (std::find(m_meshes.begin(), m_meshes.end(), mesh) == m_meshes.end()) {
                    m_meshes.push_back(mesh);
                }
                break;
            }
            case COMP_RIGIDBODY: {
                Rigidbody *rigidbody = (Rigidbody *)entity->get_component(type);
                m_physics.add_rigid_body(rigidbody);
                break;
            }
            case COMP_CAMERA: {
                Camera *camera = (Camera*)entity->get_component(type);
                if (std::find(m_cameras.begin(), m_cameras.end(), camera) == m_cameras.end()) {
                    m_cameras.push_back(camera);
                }
                break;
            }
            case COMP_LIGHT: {
                Light *light = (Light*)entity->get_component(type);
                if (std::find(m_lights.begin(), m_lights.end(), light) == m_lights.end()) {
                    m_lights.push_back(light);
                }
                break;
            }
            case COMP_MODEL: {
                Model *model = (Model*)entity->get_component(type);

                std::vector<Mesh*> meshes;
                model->get_meshes(meshes);

                for (unsigned int i = 0; i < meshes.size(); i++) {
                    if (std::find(m_meshes.begin(), m_meshes.end(), meshes[i]) == m_meshes.end()) {
                        m_meshes.push_back(meshes[i]);
                    }
                }
                break;
            }
            default:
                break;
        }
    }
}

/* handle_remove_component
 */
void Engine::handle_remove_component(Entity *entity, Component *component, eComponentType type) {
    if (entity->has_component(type)) {
        switch (type) {
            case COMP_MESH: {
                Mesh *mesh = (Mesh*)entity->get_component(type);
                auto it = std::find(m_meshes.begin(), m_meshes.end(), mesh);
                if (it != m_meshes.end()) {
                    m_meshes.erase(it);
                }
                break;
            }
            case COMP_RIGIDBODY: {
                Rigidbody *rigidbody = (Rigidbody *)entity->get_component(type);
                // TODO
                break;
            }
            case COMP_CAMERA: {
                Camera *camera = (Camera*)entity->get_component(type);
                auto it = std::find(m_cameras.begin(), m_cameras.end(), camera);
                if (it != m_cameras.end()) {
                    m_cameras.erase(it);
                }
                break;
            }
            case COMP_LIGHT: {
                Light *light = (Light*)entity->get_component(type);
                auto it = std::find(m_lights.begin(), m_lights.end(), light);
                if (it != m_lights.end()) {
                    m_lights.erase(it);
                }
                break;
            }
            case COMP_MODEL: {
                Model *model = (Model*)entity->get_component(type);

                std::vector<Mesh*> meshes;
                model->get_meshes(meshes);

                for (unsigned int i = 0; i < meshes.size(); i++) {
                    auto it = std::find(m_meshes.begin(), m_meshes.end(), meshes[i]);
                    if (it != m_meshes.end()) {
                        m_meshes.erase(it);
                    }
                }
                break;
            }
            default:
                break;
        }
    }
}

/* _process_mouse_button
 */
void Engine::_process_mouse_button(GLFWwindow *window, int button, int action, int mods) {
    Engine *engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    engine->process_mouse_button(button, action, mods);
}

/* _process_mouse_input
 */
void Engine::_process_mouse_input(GLFWwindow *window, double x, double y) {
    Engine *engine = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    engine->process_mouse_input(x, y);
}