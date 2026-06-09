#include "Shader.h"


/* Shader
 */
Shader::Shader():
m_vertex_shader_path(""),
m_fragment_shader_path(""),
m_is_valid(false)
{

}

/* Shader
 */
void Shader::load(const std::string &vertex_shader_path, const std::string &fragment_shader_path) {
    m_vertex_shader_path = vertex_shader_path;
    m_fragment_shader_path = fragment_shader_path;
    m_is_valid = false;

    unsigned int vertex_shader_id;
    unsigned int fragment_shader_id;
    if (this->load_shader(m_vertex_shader_path, SHADER_VERTEX, vertex_shader_id) &&
        this->load_shader(m_fragment_shader_path, SHADER_FRAGMENT, fragment_shader_id))
    {
        if (this->link_shader_program(vertex_shader_id, fragment_shader_id)) {
            m_is_valid = true;
        }
        else {
            std::cerr << "ERROR: Shader failed to link: " << m_vertex_shader_path << ", " << fragment_shader_path << std::endl;
        }
    }
}

/* enable
 */
void Shader::enable() {
    if (m_is_valid) {
        glUseProgram(m_program_id);
    }
    else {
        std::cerr << "ERROR: Failed to enable shader. Shader invalid." << std::endl;
    }
}

/* disable
 */
void Shader::disable() {
    if (m_is_valid) {
        glUseProgram(0);
    }
    else {
        std::cerr << "ERROR: Failed to disable shader. Shader invalid." << std::endl;
    }
}

/* is_valid
 */
bool Shader::is_valid() const {
    return m_is_valid;
}

/* get_program_id
 */
unsigned int Shader::get_program_id() const {
    return m_program_id;
}

/* set_int
 */
void Shader::set_int(const std::string &variable, int value) {
    unsigned int location = glGetUniformLocation(m_program_id, variable.c_str());
    glUniform1i(location, value);
}

/* set_float
 */
void Shader::set_float(const std::string &variable, float value) {
    unsigned int location = glGetUniformLocation(m_program_id, variable.c_str());
    glUniform1f(location, value);
}

/* set_bool
 */
void Shader::set_bool(const std::string &variable, bool value) {
    unsigned int location = glGetUniformLocation(m_program_id, variable.c_str());
    glUniform1i(location, value);
}

/* set_mat4
 */
void Shader::set_mat4(const std::string &variable, mat4 matrix) {
    unsigned int location = glGetUniformLocation(m_program_id, variable.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

/* set_vec2
 */
void Shader::set_vec2(const std::string &variable, vec2 vector) {
    unsigned int location = glGetUniformLocation(m_program_id, variable.c_str());
    glUniform2fv(location, 1, &vector[0]);
}

/* set_vec3
 */
void Shader::set_vec3(const std::string &variable, vec3 vector) {
    unsigned int location = glGetUniformLocation(m_program_id, variable.c_str());
    glUniform3fv(location, 1, &vector[0]);
}

/* load_shader
 */
bool Shader::load_shader(const std::string &filename, eShaderType shader_type, unsigned int &shader_id) {
    std::ifstream file;
    std::string content;
    int success;
    char info_log[512];

    // Read content from GLSL file
    file.open(filename);
    if (file.is_open()) {
        std::string line = "";
        while (!file.eof()) {
            std::getline(file, line);
            content.append(line + "\n");
        }
    }
    else {
        std::cerr <<  "Failed to open file " << filename << std::endl;
        return false;
    }
    file.close();

    const char *buffer = content.c_str();

    // Compile shader
    if (shader_type == SHADER_VERTEX) {
        shader_id = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (shader_type == SHADER_FRAGMENT) {
        shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    }

    glShaderSource(shader_id, 1, &buffer, NULL);
    glCompileShader(shader_id);

    // Get shader compilation status
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, NULL, info_log);
        if (shader_type == SHADER_VERTEX) {
            std::cerr << "ERROR: Vertex Shader compilation FAILED\n" << info_log << std::endl;
        }
        else if (shader_type == SHADER_FRAGMENT) {
            std::cerr << "ERROR: Fragment Shader compilation FAILED\n" << info_log << std::endl;
        }
        return false;
    }

    return true;
}

/* link_shader_program
 */
bool Shader::link_shader_program(unsigned int vertex_shader_id, unsigned int fragment_shader_id) {
    int success;
    char info_log[512];

    m_program_id = glCreateProgram();

    // Link shader program
    glAttachShader(m_program_id, vertex_shader_id);
    glAttachShader(m_program_id, fragment_shader_id);
    glLinkProgram(m_program_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    // Get shader program link status
    glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_program_id, 512, NULL, info_log);
        std::cerr << "ERROR: Shader linking FAILED\n" << info_log << std::endl;
        return false;
    }

    return true;
}
