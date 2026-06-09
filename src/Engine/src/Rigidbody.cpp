#include "Rigidbody.h"
#include "Physics.h"


/* Rigidbody
 */
Rigidbody::Rigidbody(Entity *object, float mass, bool dynamic):
p_object(object),
m_mass(btScalar(mass)),
m_is_dynamic(dynamic)
{
    Transform transform = p_object->get_transform();

    btCollisionShape *shape = new btBoxShape(btVector3(btScalar(transform.size.x / 2), btScalar(transform.size.y / 2), btScalar(transform.size.z / 2)));

    m_transform.setIdentity();
    m_transform.setOrigin(btVector3(transform.position.x, transform.position.y, transform.position.z));
    m_transform.setRotation(btQuaternion(btScalar(transform.rotation.z * DEG_TO_RAD), btScalar(transform.rotation.y * DEG_TO_RAD), btScalar(transform.rotation.x * DEG_TO_RAD)));

    btVector3 inertia(0, 0, 0);
    if (m_mass != 0.f) {
        shape->calculateLocalInertia(m_mass, inertia);
    }

    p_motion_state = new btDefaultMotionState(m_transform);
    btRigidBody::btRigidBodyConstructionInfo rb_info(m_mass, p_motion_state, shape, inertia);

    if (m_is_dynamic) {
        rb_info.m_friction = 0;
        rb_info.m_restitution = 0;
        rb_info.m_linearDamping = 0;
    }

    p_body = new btRigidBody(rb_info);

    if (m_is_dynamic) {
        p_body->setAngularFactor(0);
        p_body->setActivationState(DISABLE_DEACTIVATION);
    }

    // Create ghost object synchronized with 
    p_ghost_object = new btPairCachingGhostObject();

    p_ghost_object->setCollisionShape(shape);
    p_ghost_object->setUserPointer(this);
    p_ghost_object->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

/* ~Rigidbody
 */
Rigidbody::~Rigidbody() {
    delete p_motion_state;
    delete p_body;
    delete p_ghost_object;
}

/* update
 */
void Rigidbody::update(float delta_time) {
    btTransform trans;
    if (p_body && p_body->getMotionState()) {
        p_body->getMotionState()->getWorldTransform(trans);
    }

    vec3 pos = vec3(float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));

    Transform transform;
    transform = this->get_transform();

    btQuaternion q = trans.getRotation();

    vec3 rotation = vec3(0, 0, 0);
    btScalar yaw, pitch, roll;      // Z, Y, X
    q.getEulerZYX(yaw, pitch, roll);
    rotation.x = (float)roll * RAD_TO_DEG;
    rotation.y = (float)pitch * RAD_TO_DEG;
    rotation.z = (float)yaw * RAD_TO_DEG;
    transform.rotation = rotation;
    transform.position = pos;

    this->set_transform(transform);
}

/* set_transform
 */
void Rigidbody::set_transform(Transform transform) {
    p_object->set_transform(transform);
}

/* get_transform
 */
Transform Rigidbody::get_transform() const {
    return p_object->get_transform();
}

/* set_physics_world
 */
void Rigidbody::set_physics_world(Physics *world) {
    p_physics_world = world;
}

/* get_body
 */
btRigidBody *Rigidbody::get_body() {
    return p_body;
}

/* get_collision_object
 */
btPairCachingGhostObject *Rigidbody::get_collision_object() {
    return p_ghost_object;
}

/* is_dynamic
 */
bool Rigidbody::is_dynamic() const {
    return m_is_dynamic;
}