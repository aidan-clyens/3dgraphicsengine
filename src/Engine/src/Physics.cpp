#include "Engine/Physics.h"


/* Physics
 */
Physics::Physics() {
    p_collision_configuration = new btDefaultCollisionConfiguration();
    p_collision_dispatcher = new btCollisionDispatcher(p_collision_configuration);
    p_broadphase_interface = new btDbvtBroadphase();
    p_constraint_solver = new btSequentialImpulseConstraintSolver();
    p_dynamics_world = new btDiscreteDynamicsWorld(p_collision_dispatcher, p_broadphase_interface, p_constraint_solver, p_collision_configuration);

    p_dynamics_world->setGravity(btVector3(0, -9.8, 0));
}

/* ~Physics
 */
Physics::~Physics() {
    delete p_collision_configuration;
    delete p_collision_dispatcher;
    delete p_broadphase_interface;
    delete p_constraint_solver;
    delete p_dynamics_world;
}

/* add_rigid_body
 */
void Physics::add_rigid_body(Rigidbody *body) {
    body->set_physics_world(this);
    m_bodies.push_back(body);
    p_dynamics_world->addRigidBody(body->get_body());
    p_dynamics_world->addCollisionObject(body->get_collision_object(), btBroadphaseProxy::KinematicFilter, btBroadphaseProxy::StaticFilter | btBroadphaseProxy::DefaultFilter);
}

/* update
 */
void Physics::update(float delta_time) {
    p_dynamics_world->stepSimulation(delta_time);

    for (int i = 0; i < m_bodies.size(); i++) {
        m_bodies[i]->update(delta_time);
    }
}

/* get_dynamics_world
 */
btDiscreteDynamicsWorld *Physics::get_dynamics_world() {
    return p_dynamics_world;
}

/* cleanup
 */
void Physics::cleanup() {
    for (int i = p_dynamics_world->getNumCollisionObjects() - 1; i >= 0; i--) {
        btCollisionObject *obj = p_dynamics_world->getCollisionObjectArray()[i];
        btRigidBody *body = btRigidBody::upcast(obj);
        if (body && body->getMotionState()) {
            delete body->getMotionState();
        }
        p_dynamics_world->removeCollisionObject(obj);
        delete obj;
    }
}