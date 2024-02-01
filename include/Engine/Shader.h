#pragma once

// Includes
#include "Engine/utils/types.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

/* eShaderType
 */
typedef enum
{
    SHADER_VERTEX,
    SHADER_FRAGMENT
} eShaderType;

/* eShaderType
 */
class Shader {
    public:
        Shader();

        void load(const std::string &vertex_shader_path, const std::string &fragment_shader_path);

        void enable();
        void disable();

        bool is_valid() const;
        unsigned int get_program_id() const;

        void set_int(const std::string &variable, int value);
        void set_float(const std::string &variable, float value);
        void set_bool(const std::string &variable, bool value);
        void set_mat4(const std::string &variable, mat4 matrix);
        void set_vec2(const std::string &variable, vec2 vector);
        void set_vec3(const std::string &variable, vec3 vector);

    private:
        bool load_shader(const std::string &filename, eShaderType shader_type, unsigned int &shader_id);
        bool link_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id);

        std::string m_vertex_shader_path;
        std::string m_fragment_shader_path;

        unsigned int m_program_id;
        bool m_is_valid;
};