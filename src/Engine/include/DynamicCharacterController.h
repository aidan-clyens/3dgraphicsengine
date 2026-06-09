#pragma once

// Includes
#include "ECS.h"
#include "Rigidbody.h"
#include "Camera.h"

#include <glm/glm.hpp>

#define MAX_SPEED                   80.0f
#define DECELERATION_COEFFICIENT    15.0f
#define JUMP_RECHARGE_TIME          1
#define JUMP_IMPULSE                5.0f


/* IgnoreBodyAndGhostCast
 */
class IgnoreBodyAndGhostCast : public btCollisionWorld::ClosestRayResultCallback {
    public:
        /* IgnoreBodyAndGhostCast
         */
        IgnoreBodyAndGhostCast(btRigidBody *body, btPairCachingGhostObject *ghost):
        btCollisionWorld::ClosestRayResultCallback(btVector3(0, 0, 0), btVector3(0, 0, 0)),
        p_body(body),
        p_ghost_object(ghost)
        {

        }

        /* addSingleResult
         */
        btScalar addSingleResult(btCollisionWorld::LocalRayResult &ray_result, bool normal_in_world_space) {
            if (ray_result.m_collisionObject == p_body || ray_result.m_collisionObject == p_ghost_object) {
                return 1.0f;
            }

            return ClosestRayResultCallback::addSingleResult(ray_result, normal_in_world_space);
        }

    private:
        btRigidBody *p_body;
        btPairCachingGhostObject *p_ghost_object;
};

/* DynamicCharacterController
 */
class DynamicCharacterController : public Rigidbody {
    public:
        DynamicCharacterController(Entity *object, float mass);

        void move(vec2 direction);
        void jump();

        void update(float delta_time);

        void update_velocity(float delta_time);
        void update_position();
    
    private:
        btVector3 m_velocity;
        btVector3 m_previous_position;

        bool m_on_ground;

        float m_jump_timer;
};