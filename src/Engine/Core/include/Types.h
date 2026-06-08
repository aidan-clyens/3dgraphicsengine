#pragma once

// Includes
#include <glm/glm.hpp>

// Defines
#define MAX_POINT_LIGHTS    16

// Typedefs
typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;

// Enums
typedef enum {
    MATERIAL_COLOR,
    MATERIAL_TEXTURE_2D,
    MATERIAL_TEXTURE_CUBE
} eMaterialType;

// Structs
typedef struct {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
} Material;

/* vec2_key_hash
 */
struct vec2_key_hash {
    std::size_t operator() (const vec2 &c) const {
        int x = (int)c.x;
        int y = (int)c.y;
        return x ^ y;
    }
};

/* vec2_key_equal
 */
struct vec2_key_equal {
    bool operator() (const vec3 &c0, const vec3 &c1) const {
        return c0 == c1;
    }
};

/* vec3_key_hash
 */
struct vec3_key_hash {
    std::size_t operator() (const vec3 &c) const {
        int x = (int)c.x;
        int y = (int)c.y;
        int z = (int)c.z;
        return x ^ y ^ z;
    }
};

/* vec3_key_equal
 */
struct vec3_key_equal {
    bool operator() (const vec3 &c0, const vec3 &c1) const {
        return c0 == c1;
    }
};