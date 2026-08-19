#include "Engine.h"
#include "Cube.h"

class PrimitiveObjects : public Engine
{
public:
  void setup()
  {
    this->disable_debug_window();

    this->add_object(new Cube());
  }

  void update()
  {
  }
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