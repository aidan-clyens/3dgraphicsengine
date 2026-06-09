#pragma once

#include "ECS.h"

#include "btBulletDynamicsCommon.h"
#include "btBulletCollisionCommon.h"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

// Defines
#define DEG_TO_RAD 0.01745329251994329576923690768489
#define RAD_TO_DEG 57.295779513082320876798154814105

class Physics;

/* Rigidbody
 */
class Rigidbody : public Component {
    public:
        Rigidbody(Entity *object, float mass, bool dynamic = false);
        virtual ~Rigidbody();

        virtual void update(float delta_time);

        void set_transform(Transform transform);
        Transform get_transform() const;

        void set_physics_world(Physics *world);

        btRigidBody *get_body();
        btPairCachingGhostObject *get_collision_object();

        bool is_dynamic() const;

    protected:
        Physics *p_physics_world;

        btScalar m_mass;
        Entity *p_object;
        btTransform m_transform;
        btDefaultMotionState *p_motion_state;
        btRigidBody *p_body;
        btPairCachingGhostObject *p_ghost_object;

        bool m_is_dynamic;
};