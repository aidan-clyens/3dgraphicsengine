#include "Engine.h"
#include "GridMesh.h"

#include <cmath>

class Terrain : public Engine
{
public:
  void setup()
  {
    this->enable_debug_window();
    this->enable_mouse_cursor();

    this->set_background_color(vec3(0.1, 0.1, 0.1));

    // Set main camera position
    Camera *camera = this->get_camera();
    camera->set_position(vec3(0, 1.8, 8));
    this->set_camera(camera);

    // Build a height map
    const size_t RESOLUTION = 64;
    float height_scale = 0.3f;

    std::vector<float> heights(RESOLUTION * RESOLUTION);
    for (size_t y = 0; y < RESOLUTION; y++)
    {
      for (size_t x = 0; x < RESOLUTION; x++)
      {
        // Use a sine function to set the height value
        heights[y * RESOLUTION + x] = height_scale * (sinf((float)x * 0.3f) * cosf((float)y * 0.3f));
      }
    }

    // Create terrain plane
    Object3D *plane = Object3DFactory::create<Object3D>();
    plane->add_component(COMP_MESH, new GridMesh(RESOLUTION, heights));
    plane->set_position(vec3(0, 0, 0));
    plane->set_size(vec3(5, 1, 5));

    this->add_object(plane);
  }

  void update()
  {
  }
};

int main(int argc, char **argv)
{
  Terrain app;

  if (!app.init())
  {
    std::cerr << "Game Engine failed to initialize" << std::endl;
    return -1;
  }

  app.start();
  app.cleanup();

  return 0;
}