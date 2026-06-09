#include "ECS.h"

/* Component
 */
Component::Component() {

}

/* set_transform
 */
void Component::set_transform(Transform transform) {
    m_transform = transform;
}

/* get_transform
 */
Transform Component::get_transform() const {
    return m_transform;
}

/* get_transform
 */
void Component::set_position(const vec3 position) {
    m_transform.position = position;
}

/* get_transform
 */
vec3 Component::get_position() const {
    return m_transform.position;
}

/* Entity
 */
Entity::Entity():
p_entity_manager(nullptr)
{

}

/* ~Entity
 */
Entity::~Entity() {

}

/* add_component
 */
void Entity::add_component(int id, Component *component) {
    m_components[id] = component;
    if (p_entity_manager != nullptr) {
        p_entity_manager->handle_add_component(this, component, (eComponentType)id);
    }
}

/* remove_component
 */
void Entity::remove_component(int id) {
    if (this->has_component(id)) {
        if (p_entity_manager != nullptr) {
            p_entity_manager->handle_remove_component(this, m_components[id], (eComponentType)id);
        }
        m_components.erase(id);
    }
}

/* get_component
 */
Component *Entity::get_component(int id) {
    return m_components[id];
}

/* has_component
 */
bool Entity::has_component(int id) {
    return (m_components.find(id) != m_components.end());
}

/* assign_entity_manager
 */
void Entity::assign_entity_manager(EntityManager *manager) {
    p_entity_manager = manager;
}

/* get_transform
 */
Transform Entity::get_transform() const {
    return m_transform;
}

/* set_transform
 */
void Entity::set_transform(Transform transform) {
    m_transform = transform;

    ComponentMapIterator it;
    for (it = m_components.begin(); it != m_components.end(); it++) {
        it->second->set_transform(transform);
    }
}