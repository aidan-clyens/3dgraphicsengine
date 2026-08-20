#include "Engine.h"
#include "Cube.h"

class PrimitiveObjects : public Engine
{
public:
  void setup()
  {
    this->disable_debug_window();
    this->enable_mouse_cursor();

    this->set_background_color(vec3(0.25, 0.08, 0));

    // Create Cube Primitive
    p_cube = Object3DFactory::create<Cube>();
    p_cube->set_name("Cube");
    p_cube->set_color(vec3(0, 0, 1));

    this->add_object(p_cube);
  }

  void update()
  {
    vec3 rotation = p_cube->get_rotation();
    rotation.x += 1;
    rotation.y += 1;
    p_cube->set_rotation(rotation);
  }

private:
  Cube *p_cube;
};

int main(int argc, char **argv)
{
  PrimitiveObjects app;

  if (!app.init())
  {
    std::cerr << "Game Engine failed to initialize" << std::endl;
    return -1;
  }

  app.start();
  app.cleanup();

  return 0;
}