#pragma once

// Includes
#include "Types.h"

#include <unordered_map>

// Enums
typedef enum {
    COMP_MESH = 0,
    COMP_RIGIDBODY = 1,
    COMP_CAMERA = 2,
    COMP_LIGHT =3,
    COMP_MODEL = 4
} eComponentType;

// Structs
typedef struct {
    vec3 position;
    vec3 rotation;
    vec3 size;
} Transform;

// Forward Declarations
class Entity;

/* Component
 */
class Component {
    public:
        Component();

        virtual void set_transform(Transform transform);
        Transform get_transform() const;

        void set_position(const vec3 position);
        vec3 get_position() const;

    protected:
        Transform m_transform;
};

/* EntityManager
 */
class EntityManager {
    public:
        virtual void handle_add_component(Entity *entity, Component *component, eComponentType type) = 0;
        virtual void handle_remove_component(Entity *entity, Component *component, eComponentType type) = 0;
};

// Typedefs
typedef std::unordered_map<int, Component*> ComponentMap;
typedef std::unordered_map<int, Component*>::iterator ComponentMapIterator;

/* Entity
 */
class Entity {
    public:
        Entity();
        virtual ~Entity();

        void add_component(int id, Component *component);
        void remove_component(int id);
        Component *get_component(int id);

        bool has_component(int id);

        void assign_entity_manager(EntityManager *manager);

        Transform get_transform() const;
        void set_transform(Transform transform);

    protected:
        EntityManager *p_entity_manager;
        ComponentMap m_components;

        Transform m_transform;
};