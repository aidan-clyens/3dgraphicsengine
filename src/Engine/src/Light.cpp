#include "Engine/Light.h"

// Data
// constant, linear, quadratic
float point_light_constants[] = {
    1.0, 	0.7, 	    1.8,
    1.0, 	0.35, 	    0.44,
    1.0, 	0.22, 	    0.20,
    1.0, 	0.14, 	    0.07,
    1.0, 	0.09, 	    0.032,
    1.0, 	0.07, 	    0.017,
    1.0, 	0.045, 	    0.0075,
    1.0, 	0.027, 	    0.0028,
    1.0, 	0.022, 	    0.0019,
    1.0, 	0.014, 	    0.0007,
    1.0, 	0.007, 	    0.0002,
    1.0, 	0.0014, 	0.000007
};

/* Light
 */
Light::Light() {

}

/* set_lighting
 */
void Light::set_lighting(const vec3 ambient, const vec3 diffuse, const vec3 specular) {
    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;
}

/* set_ambient
 */
void Light::set_ambient(const vec3 ambient) {
    m_ambient = ambient;
}

/* set_diffuse
 */
void Light::set_diffuse(const vec3 diffuse) {
    m_diffuse = diffuse;
}

/* set_specular
 */
void Light::set_specular(const vec3 specular) {
    m_specular = specular;
}

/* get_ambient
 */
vec3 Light::get_ambient() const {
    return m_ambient;
}

/* get_diffuse
 */
vec3 Light::get_diffuse() const {
    return m_diffuse;
}

/* get_specular
 */
vec3 Light::get_specular() const {
    return m_specular;
}

/* get_id
 */
int Light::get_id() const {
    return m_id;
}

/* DirectionalLight
 */
DirectionalLight::DirectionalLight() {

}

/* set_origin
 */
void DirectionalLight::set_origin(const vec3 origin) {
    m_origin = origin;
}

/* get_origin
 */
vec3 DirectionalLight::get_origin() const {
    return m_origin;
}

/* get_direction
 */
vec3 DirectionalLight::get_direction() const {
    return m_origin - m_transform.position;
}

/* PointLight
 */
PointLight::PointLight() {

}

/* set_light_strength
 */
void PointLight::set_light_strength(ePointLightDistance distance) {
    int index = (int)distance * 3;
    float constant = point_light_constants[index];
    float linear = point_light_constants[index + 1];
    float quadratic = point_light_constants[index + 2];

    this->set_light_strength(constant, linear, quadratic);
}

/* set_light_strength
 */
void PointLight::set_light_strength(float constant, float linear, float quadratic) {
    m_constant = constant;
    m_linear = linear;
    m_quadratic = quadratic;
}

/* get_constant
 */
float PointLight::get_constant() const {
    return m_constant;
}

/* get_linear
 */
float PointLight::get_linear() const {
    return m_linear;
}

/* get_quadratic
 */
float PointLight::get_quadratic() const {
    return m_quadratic;
}