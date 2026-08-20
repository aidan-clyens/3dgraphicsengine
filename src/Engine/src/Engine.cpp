#include "Engine.h"

#include "Clock.h"
#include "Logger.h"

#include <cmath>

/* Engine
 */
Engine::Engine(int width, int height, const std::string &path) : p_input_manager(InputManager::get_instance()),
                                                                 p_camera(new Camera(vec3(0, 0, 5))),
                                                                 m_renderer(width, height, path)
{
}

/* ~Engine
 */
Engine::~Engine()
{
}

/* init
 */
bool Engine::init()
{
  if (!m_renderer.init(this))
  {
    LOG_ERROR("Engine: init - Failed to initialize Renderer! Exiting...");
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

  LOG_INFO("Engine: init - Initialized Engine with window dimensions: ", SCREEN_WIDTH, " x ", SCREEN_HEIGHT);
  return true;
}

/* start
 */
void Engine::start()
{
  this->setup();

  LOG_INFO("Engine: start - Starting game loop...");

  // Main rendering loop
  double current_frame = 0;
  double last_frame = 0;
  m_running = true;
  while (!m_renderer.is_window_closed() && m_running)
  {
    current_frame = glfwGetTime();
    m_delta_time = current_frame - last_frame;
    last_frame = current_frame;

    this->update();

#ifdef BUILD_BULLET3
    m_physics.update(m_delta_time);
#endif
    m_renderer.render(m_meshes, m_lights, *p_camera);
  }
}

/* cleanup
 */
void Engine::cleanup()
{
  for (Object3D *object : m_objects)
  {
    delete object;
  }

#ifdef BUILD_BULLET3
  m_physics.cleanup();
#endif
  m_renderer.close();

  LOG_INFO("Engine: cleanup - Cleaned up Engine resources.");
}

/* add_object
 */
void Engine::add_object(Object3D *object)
{
  object->assign_entity_manager(this);
  m_objects.push_back(object);

  LOG_INFO("Engine: add_object - ", object->to_string());

  if (object->has_component(COMP_MESH))
  {
    this->handle_add_component(object, COMP_MESH);
  }

#ifdef BUILD_BULLET3
  if (object->has_component(COMP_RIGIDBODY))
  {
    this->handle_add_component(object, COMP_RIGIDBODY);
  }
#endif

  if (object->has_component(COMP_CAMERA))
  {
    this->handle_add_component(object, COMP_CAMERA);
  }

  if (object->has_component(COMP_LIGHT))
  {
    this->handle_add_component(object, COMP_LIGHT);
  }

  if (object->has_component(COMP_MODEL))
  {
    this->handle_add_component(object, COMP_MODEL);
  }
}

/* remove_object
 */
void Engine::remove_object(Object3D *object)
{
  // Remove components
  if (object->has_component(COMP_MESH))
  {
    this->handle_remove_component(object, COMP_MESH);
  }

#ifdef BUILD_BULLET3
  if (object->has_component(COMP_RIGIDBODY))
  {
    this->handle_remove_component(object, COMP_RIGIDBODY);
  }
#endif

  if (object->has_component(COMP_CAMERA))
  {
    this->handle_remove_component(object, COMP_CAMERA);
  }

  if (object->has_component(COMP_LIGHT))
  {
    this->handle_remove_component(object, COMP_LIGHT);
  }

  if (object->has_component(COMP_MODEL))
  {
    this->handle_remove_component(object, COMP_MODEL);
  }

  // Remove object
  auto it = std::find(m_objects.begin(), m_objects.end(), object);
  if (it != m_objects.end())
  {
    m_objects.erase(it);
  }

  delete object;
}

/* get_objects
 */
void Engine::get_objects(std::vector<Object3D *> &objects)
{
  objects = m_objects;
}

Object3D *Engine::create_empty_object()
{
  return Object3DFactory::create_object();
}

Object3D *Engine::create_empty_object(vec3 position, vec3 rotation, vec3 size)
{
  return Object3DFactory::create_object(position, rotation, size);
}

/* create_model
 */
Object3D *Engine::create_model(Transform transform, const std::string &path)
{
  Object3D *object = this->create_empty_object();
  object->add_component(COMP_MODEL, new Model());

  Model *model = (Model *)object->get_component(COMP_MODEL);
  model->load_model(path);
  model->set_transform(transform);

  return object;
}

/* set_directional_light
 */
void Engine::set_directional_light(DirectionalLight light)
{
  m_renderer.set_directional_light(light);
}

/* get_directional_light
 */
DirectionalLight Engine::get_directional_light() const
{
  return m_renderer.get_directional_light();
}

/* set_background_color
 */
void Engine::set_background_color(vec3 color)
{
  m_renderer.set_background_color(color);
}

/* set_skybox
 */
void Engine::set_skybox(Object3D *skybox)
{
  m_renderer.set_skybox(skybox);
}

/* set_camera
 */
void Engine::set_camera(Camera *camera)
{
  p_camera = camera;
}

/* get_cameras
 */
void Engine::get_cameras(std::vector<Camera *> &cameras)
{
  cameras = m_cameras;
}

/* get_camera
 */
Camera *Engine::get_camera()
{
  return p_camera;
}

/* enable_mouse_cursor
 */
void Engine::enable_mouse_cursor()
{
  m_renderer.set_mouse_visible(true);
}

void Engine::disable_mouse_cursor()
{
  m_renderer.set_mouse_visible(false);
}

/* set_shadows_enabled
 */
void Engine::set_shadows_enabled(bool enable)
{
  m_renderer.set_shadows_enabled(enable);
}

void Engine::enable_debug_window()
{
  m_renderer.set_debug_window_enabled(true);
}

void Engine::disable_debug_window()
{
  m_renderer.set_debug_window_enabled(false);
}

/* get_delta_time
 */
double Engine::get_delta_time() const
{
  return m_delta_time;
}

/* get_screen_dimensions
 */
vec2 Engine::get_screen_dimensions() const
{
  return m_renderer.get_screen_size();
}

/* get_world_boundaries
 * Computes the visible world-space extent of the z=0 plane, using the
 * camera's current distance from that plane as the depth (the engine's
 * projection is a fixed perspective, so this widens/narrows with distance -
 * it is not a fixed rectangle for arbitrary depths).
 */
WorldBounds Engine::get_world_boundaries() const
{
  vec3 camera_position = p_camera->get_position();
  vec2 screen_size = m_renderer.get_screen_size();

  float aspect_ratio = screen_size.x / screen_size.y;
  float depth = std::abs(camera_position.z);

  float half_height = depth * tanf(glm::radians(CAMERA_FOV_DEGREES) / 2.0f);
  float half_width = half_height * aspect_ratio;

  WorldBounds bounds;
  bounds.min = vec2(camera_position.x - half_width, camera_position.y - half_height);
  bounds.max = vec2(camera_position.x + half_width, camera_position.y + half_height);

  return bounds;
}

/* process_mouse_button
 */
void Engine::process_mouse_button(int button, int action, int mods)
{
  (void)mods;
  if (m_renderer.is_debug_window_enabled())
    DebugWindow::add_mouse_button_event(button, action);
}

/* process_mouse_input
 */
void Engine::process_mouse_input(double x, double y)
{
  p_input_manager->process_mouse_input(x, y);
  if (m_renderer.is_debug_window_enabled())
    DebugWindow::add_mouse_position_event(x, y);
}

/* get_window
 */
GLFWwindow *Engine::get_window()
{
  return m_renderer.get_window();
}

/* get_lighting_info
 */
LightingInfo Engine::get_lighting_info() const
{
  return m_renderer.get_lighting_info();
}

/* set_lighting_info
 */
void Engine::set_lighting_info(LightingInfo info)
{
  m_renderer.set_lighting_info(info);
}

/* handle_add_component
 */
void Engine::handle_add_component(IEntity *entity, eComponentType type)
{
  LOG_INFO("Engine: handle_add_component - Adding Component type: ", component_type_to_string(type));

  if (entity->has_component(type))
  {
    switch (type)
    {
    case COMP_MESH:
    {
      Mesh *mesh = (Mesh *)entity->get_component(type);
      if (std::find(m_meshes.begin(), m_meshes.end(), mesh) == m_meshes.end())
      {
        m_meshes.push_back(mesh);
        LOG_INFO("Engine: handle_add_component - Added ", mesh->to_string());
      }
      break;
    }
#ifdef BUILD_BULLET3
    case COMP_RIGIDBODY:
    {
      Rigidbody *rigidbody = (Rigidbody *)entity->get_component(type);
      m_physics.add_rigid_body(rigidbody);
      break;
    }
#endif
    case COMP_CAMERA:
    {
      Camera *camera = (Camera *)entity->get_component(type);
      if (std::find(m_cameras.begin(), m_cameras.end(), camera) == m_cameras.end())
      {
        m_cameras.push_back(camera);
      }
      break;
    }
    case COMP_LIGHT:
    {
      Light *light = (Light *)entity->get_component(type);
      if (std::find(m_lights.begin(), m_lights.end(), light) == m_lights.end())
      {
        m_lights.push_back(light);
      }
      break;
    }
    case COMP_MODEL:
    {
      Model *model = (Model *)entity->get_component(type);

      std::vector<Mesh *> meshes;
      model->get_meshes(meshes);

      for (unsigned int i = 0; i < meshes.size(); i++)
      {
        if (std::find(m_meshes.begin(), m_meshes.end(), meshes[i]) == m_meshes.end())
        {
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
void Engine::handle_remove_component(IEntity *entity, eComponentType type)
{
  LOG_INFO("Engine: handle_remove_component - Removing Component type: ", type);

  if (entity->has_component(type))
  {
    switch (type)
    {
    case COMP_MESH:
    {
      Mesh *mesh = (Mesh *)entity->get_component(type);
      auto it = std::find(m_meshes.begin(), m_meshes.end(), mesh);
      if (it != m_meshes.end())
      {
        m_meshes.erase(it);
        LOG_INFO("Engine: handle_remove_component - Erased ", mesh->to_string());
      }
      break;
    }
#ifdef BUILD_BULLET3
    case COMP_RIGIDBODY:
    {
      Rigidbody *rigidbody = (Rigidbody *)entity->get_component(type);
      (void)rigidbody;
      // TODO - Implement remove_component - Rigidbody
      break;
    }
#endif
    case COMP_CAMERA:
    {
      Camera *camera = (Camera *)entity->get_component(type);
      auto it = std::find(m_cameras.begin(), m_cameras.end(), camera);
      if (it != m_cameras.end())
      {
        m_cameras.erase(it);
      }
      break;
    }
    case COMP_LIGHT:
    {
      Light *light = (Light *)entity->get_component(type);
      auto it = std::find(m_lights.begin(), m_lights.end(), light);
      if (it != m_lights.end())
      {
        m_lights.erase(it);
      }
      break;
    }
    case COMP_MODEL:
    {
      Model *model = (Model *)entity->get_component(type);

      std::vector<Mesh *> meshes;
      model->get_meshes(meshes);

      for (unsigned int i = 0; i < meshes.size(); i++)
      {
        auto it = std::find(m_meshes.begin(), m_meshes.end(), meshes[i]);
        if (it != m_meshes.end())
        {
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
void Engine::_process_mouse_button(GLFWwindow *window, int button, int action, int mods)
{
  Engine *engine = static_cast<Engine *>(glfwGetWindowUserPointer(window));
  engine->process_mouse_button(button, action, mods);
}

/* _process_mouse_input
 */
void Engine::_process_mouse_input(GLFWwindow *window, double x, double y)
{
  Engine *engine = static_cast<Engine *>(glfwGetWindowUserPointer(window));
  engine->process_mouse_input(x, y);
}