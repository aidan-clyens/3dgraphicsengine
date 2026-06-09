#include "DynamicCharacterController.h"
#include "Physics.h"

#include <iostream>

/* DynamicCharacterController
 */
DynamicCharacterController::DynamicCharacterController(Entity *object, float mass):
Rigidbody(object, mass, true),
m_velocity(0, 0, 0),
m_previous_position(0, 0, 0),
m_on_ground(false),
m_jump_timer(0)
{

}

/* move
 */
void DynamicCharacterController::move(vec2 direction) {
    vec2 velocity = direction + vec2(m_velocity.getX(), m_velocity.getZ());

    float speed = std::min(std::abs(glm::length(velocity)), MAX_SPEED);
    
    if (speed > 0) {
        vec2 velocity_unit = glm::normalize(velocity);
        velocity = velocity_unit * speed;
    }

    m_velocity.setX(velocity.x);
    m_velocity.setZ(velocity.y);
}

/* jump
 */
void DynamicCharacterController::jump() {
    if (m_on_ground && m_jump_timer >= JUMP_RECHARGE_TIME) {
        p_body->applyCentralImpulse(btVector3(0, JUMP_IMPULSE, 0));

        float offset = 0.01f;
        float prev_y = p_body->getWorldTransform().getOrigin().getY();

        p_body->getWorldTransform().getOrigin().setY(prev_y + offset);

        m_jump_timer = 0;
        m_on_ground = false;
    }
}

/* update
 */
void DynamicCharacterController::update(float delta_time) {
    p_ghost_object->setWorldTransform(p_body->getWorldTransform());

    p_motion_state->getWorldTransform(m_transform);

    this->update_position();
    this->update_velocity(delta_time);

    if (m_jump_timer < JUMP_RECHARGE_TIME) {
        m_jump_timer += delta_time;
    }
}

/* update_velocity
 */
void DynamicCharacterController::update_velocity(float delta_time) {
    m_velocity.setY(p_body->getLinearVelocity().getY());
    p_body->setLinearVelocity(m_velocity);

    // Decelerate
    m_velocity -= m_velocity * DECELERATION_COEFFICIENT * delta_time;
}

/* update_position
 */
void DynamicCharacterController::update_position() {
    // Check for collision at bottom of body
    IgnoreBodyAndGhostCast ray_callback_bottom(p_body, p_ghost_object);

    p_physics_world->get_dynamics_world()->rayTest(
        p_body->getWorldTransform().getOrigin(),
        p_body->getWorldTransform().getOrigin() - btVector3(0, this->get_transform().size.y, 0),
        ray_callback_bottom
    );

    if (ray_callback_bottom.hasHit()) {
        btVector3 pos = p_body->getWorldTransform().getOrigin();
        pos.setY(m_previous_position.getY());
        p_body->getWorldTransform().setOrigin(pos);

        m_velocity.setY(0);
        p_body->setLinearVelocity(m_velocity);

        m_on_ground = true;
    }

    m_previous_position = p_body->getWorldTransform().getOrigin();

    Transform transform = this->get_transform();
    transform.position = vec3(m_previous_position.getX(), m_previous_position.getY(), m_previous_position.getZ());
    this->set_transform(transform);
}