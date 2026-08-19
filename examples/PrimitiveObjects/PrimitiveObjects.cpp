#include "Engine.h"
#include "Cube.h"

class PrimitiveObjects : public Engine
{
public:
  void setup()
  {
    this->disable_debug_window();

    p_cube = Object3DFactory::create<Cube>();
    this->add_object(p_cube);
  }

  void update()
  {
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