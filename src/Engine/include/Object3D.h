#pragma once

// Includes
#include "Types.h"
#include "ECS.h"
#include "Mesh.h"
#include "Light.h"

#include <string>

/* Object3D
 */
class Object3D : public IEntity
{
  friend class Object3DFactory;

public:
  virtual ~Object3D();

  vec3 get_position() const;
  vec3 get_rotation() const;
  vec3 get_size() const;

  void set_position(vec3 position);
  void set_rotation(vec3 rotation);
  void set_size(vec3 size);

  std::string get_name() const;
  void set_name(const std::string &name);

  std::string to_string() const;

protected:
  explicit Object3D();
  Object3D(vec3 pos, vec3 rotation, vec3 size);

  std::string m_name;
};

std::ostream &operator<<(std::ostream &os, const Object3D &obj);

class Object3DFactory
{
public:
  static Object3D *create_object();
  static Object3D *create_object(vec3 position, vec3 rotation, vec3 size);
};