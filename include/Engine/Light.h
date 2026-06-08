#pragma once

// Includes
#include "ECS.h"
#include "Types.h"

// Enums
/* ePointLightDistance
 */
typedef enum {
    LIGHT_DISTANCE_7,
    LIGHT_DISTANCE_13,
    LIGHT_DISTANCE_20,
    LIGHT_DISTANCE_32,
    LIGHT_DISTANCE_50,
    LIGHT_DISTANCE_65,
    LIGHT_DISTANCE_100,
    LIGHT_DISTANCE_160,
    LIGHT_DISTANCE_200,
    LIGHT_DISTANCE_325,
    LIGHT_DISTANCE_600,
    LIGHT_DISTANCE_3250,
} ePointLightDistance;

/* Light
 */
class Light : public Component {
    public:
        Light();

        void set_lighting(const vec3 ambient, const vec3 diffuse, const vec3 specular);

        void set_ambient(const vec3 ambient);
        void set_diffuse(const vec3 diffuse);
        void set_specular(const vec3 specular);

        vec3 get_ambient() const;
        vec3 get_diffuse() const;
        vec3 get_specular() const;

        int get_id() const;

    protected:
        int m_id;

        vec3 m_ambient;
        vec3 m_diffuse;
        vec3 m_specular;
};

/* DirectionalLight
 */
class DirectionalLight : public Light {
    public:
        DirectionalLight();

        void set_origin(const vec3 origin);

        vec3 get_origin() const;
        vec3 get_direction() const;

    private:
        vec3 m_origin;
};

/* PointLight
 */
class PointLight : public Light {
    public:
        PointLight();

        void set_light_strength(ePointLightDistance distance);
        void set_light_strength(float constant, float linear, float quadratic);

        float get_constant() const;
        float get_linear() const;
        float get_quadratic() const;

    private:
        // Used to calculate attenuation for point lights
        float m_constant;
        float m_linear;
        float m_quadratic;
};
