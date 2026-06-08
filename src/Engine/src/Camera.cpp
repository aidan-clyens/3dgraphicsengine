#include "Engine/Camera.h"


/* Camera
 */
Camera::Camera():
m_position(vec3(0.0, 0.0, 0.0)),
m_front(vec3(0.0, 0.0, -1.0)),
m_up(vec3(0.0, 1.0, 0.0)),
m_yaw(0),
m_pitch(0)
{

}

/* Camera
 */
Camera::Camera(vec3 position):
m_position(position),
m_front(vec3(0.0, 0.0, -1.0)),
m_up(vec3(0.0, 1.0, 0.0)),
m_yaw(0),
m_pitch(0)
{

}

/* set_position
 */
void Camera::set_position(vec3 position) {
    m_position = position;
}

/* get_position
 */
vec3 Camera::get_position() const {
    return m_position;
}

/* set_position
 */
void Camera::set_mouse_offset(double offset_x, double offset_y) {
    m_yaw += offset_x;
    m_pitch += offset_y;

    if (m_pitch > 89.0) {
        m_pitch = 89.0;
    }
    if (m_pitch < -89.0) {
        m_pitch = -89.0;
    }

    vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

    m_front = glm::normalize(direction);
}

/* translate_x
 */
void Camera::translate_x(float speed) {
    m_position += speed * m_front;
}

/* translate_y
 */
void Camera::translate_y(float speed) {
    m_position += speed * m_up;
}

/* translate_z
 */
void Camera::translate_z(float speed) {
    m_position += speed * glm::normalize(glm::cross(m_front, m_up));
}

/* front
 */
vec3 Camera::front() const {
    return m_front;
}

/* up
 */
vec3 Camera::up() const {
    return m_up;
}

/* right
 */
vec3 Camera::right() const {
    return glm::normalize(glm::cross(m_front, m_up));
}