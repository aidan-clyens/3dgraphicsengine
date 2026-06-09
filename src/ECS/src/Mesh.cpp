#include "Mesh.h"


/* Mesh
 */
Mesh::Mesh():
m_use_shader(false),
m_use_texture(false),
m_num_vertices(0),
m_material_type(MATERIAL_COLOR)
{
    this->init_mesh();
}

/* Mesh
 */
Mesh::Mesh(std::vector<Vertex> vertices):
m_use_shader(false),
m_use_texture(false),
m_num_vertices(vertices.size()),
m_material_type(MATERIAL_COLOR)
{
    m_vertices = vertices;
    this->init_mesh();
    this->create_mesh();
}

/* ~Mesh
 */
Mesh::~Mesh() {
    glDeleteBuffers(1, &m_vertex_buffer_object);
    glDeleteBuffers(1, &m_element_buffer_object);
    glDeleteBuffers(1, &m_instance_buffer_object);
    glDeleteVertexArrays(1, &m_vertex_array_object);

    delete m_vertex_buffer.data;
    delete m_normal_buffer.data;
    delete m_uv_buffer.data;
}

/* render
 */
void Mesh::init_mesh() {
    // Create VBO and VAO
    glGenVertexArrays(1, &m_vertex_array_object);
    glGenBuffers(1, &m_vertex_buffer_object);
    glGenBuffers(1, &m_element_buffer_object);
    glGenBuffers(1, &m_instance_buffer_object);

    // Initialize material lighting data
    m_material.ambient = vec3(1, 1, 1);
    m_material.diffuse = vec3(1, 1, 1);
    m_material.specular = vec3(1, 1, 1);
    m_material.shininess = 32;

    // Initialize transform
    m_transform.position = vec3(0, 0, 0);
    m_transform.rotation = vec3(0, 0, 0);
    m_transform.size = vec3(1, 1, 1);

    // Create transformations
    set_transform(m_transform);
}

/* create_mesh
 */
void Mesh::create_mesh() {
    if (m_num_vertices == 0)
        return;

    m_vertex_buffer.stride = 3;
    m_vertex_buffer.size = sizeof(float) * m_vertex_buffer.stride * m_num_vertices;
    m_vertex_buffer.data = new float[m_vertex_buffer.size];

    m_normal_buffer.stride = 3;
    m_normal_buffer.size = sizeof(float) * m_normal_buffer.stride * m_num_vertices;
    m_normal_buffer.data = new float[m_normal_buffer.size];

    m_uv_buffer.stride = 2;
    m_uv_buffer.size = sizeof(float) * m_uv_buffer.stride * m_num_vertices;
    m_uv_buffer.data = new float[m_uv_buffer.size];

    // Vertices
    int index = 0;
    for (unsigned int i = 0; i < m_vertex_buffer.stride * m_num_vertices; i += m_vertex_buffer.stride) {
        m_vertex_buffer.data[i] = m_vertices[index].vertex.x;
        m_vertex_buffer.data[i+1] = m_vertices[index].vertex.y;
        m_vertex_buffer.data[i+2] = m_vertices[index].vertex.z;
        index++;
    }

    // Normals
    index = 0;
    for (unsigned int i = 0; i < m_normal_buffer.stride * m_num_vertices; i += m_normal_buffer.stride) {
        m_normal_buffer.data[i] = m_vertices[index].normal.x;
        m_normal_buffer.data[i+1] = m_vertices[index].normal.y;
        m_normal_buffer.data[i+2] = m_vertices[index].normal.z;
        index++;
    }

    // UVs
    index = 0;
    for (unsigned int i = 0; i < m_uv_buffer.stride * m_num_vertices; i += m_uv_buffer.stride) {
        m_uv_buffer.data[i] = m_vertices[index].uv.x;
        m_uv_buffer.data[i+1] = m_vertices[index].uv.y;
        index++;
    }
}

/* render
 */
void Mesh::render() {
    if (m_num_vertices == 0)
        return;

    glBindVertexArray(m_vertex_array_object);

    // Vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_buffer.size + m_normal_buffer.size + m_uv_buffer.size, nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertex_buffer.size, m_vertex_buffer.data);
    glBufferSubData(GL_ARRAY_BUFFER, m_vertex_buffer.size, m_normal_buffer.size, m_normal_buffer.data);
    glBufferSubData(GL_ARRAY_BUFFER, m_vertex_buffer.size + m_normal_buffer.size, m_uv_buffer.size, m_vertex_buffer.data);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, m_vertex_buffer.stride, GL_FLOAT, GL_FALSE, m_vertex_buffer.stride * sizeof(float), (void *)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, m_normal_buffer.stride, GL_FLOAT, GL_FALSE, m_normal_buffer.stride * sizeof(float), (void *)(m_vertex_buffer.size));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, m_uv_buffer.stride, GL_FLOAT, GL_FALSE, m_uv_buffer.stride * sizeof(float), (void *)(m_vertex_buffer.size + m_normal_buffer.size));

    // Instance buffer object
    glBindBuffer(GL_ARRAY_BUFFER, m_instance_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mat4), &m_model, GL_STATIC_DRAW);

    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)0);

    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)(sizeof(vec4)));

    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)(2 * sizeof(vec4)));

    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void *)(3 * sizeof(vec4)));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);

    if (m_use_texture) {
        m_texture.enable();
    }

    glDrawArrays(GL_TRIANGLES, 0, m_num_vertices);

    if (m_use_texture) {
        m_texture.disable();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

/* set_transform
 */
void Mesh::set_transform(Transform transform) {
    Component::set_transform(transform);

    // Create transformations
    m_model = mat4(1.0);

    // Transform object
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.x), vec3(1.0, 0.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.y), vec3(0.0, 1.0, 0.0));
    m_model = glm::rotate(m_model, glm::radians((float)m_transform.rotation.z), vec3(0.0, 0.0, 1.0));
    m_model = glm::translate(m_model, m_transform.position);
    m_model = glm::scale(m_model, m_transform.size);
}

/* set_shader
 */
void Mesh::set_shader(Shader &shader) {
    m_shader = shader;
    m_use_shader = true;
}

/* set_texture
 */
void Mesh::set_texture(Texture texture) {
    m_texture = texture;
    m_use_texture = true;

    switch (m_texture.get_texture_type()) {
        case GL_TEXTURE_2D:
            m_material_type = MATERIAL_TEXTURE_2D;
            break;
        case GL_TEXTURE_CUBE_MAP:
            m_material_type = MATERIAL_TEXTURE_CUBE;
            break;
        default:
            m_material_type = MATERIAL_COLOR;
            break;
    }
}

/* set_material
 */
void Mesh::set_material(Material material) {
    m_material = material;
}

/* get_material
 */
Material Mesh::get_material() const {
    return m_material;
}

/* get_texture
 */
Texture Mesh::get_texture() const {
    return m_texture;
}

/* has_shader
 */
bool Mesh::has_shader() const {
    return m_use_shader;
}

/* has_texture
 */
bool Mesh::has_texture() const {
    return m_use_texture;
}

/* get_material_type
 */
eMaterialType Mesh::get_material_type() const {
    return m_material_type;
}

/* get_num_vertices
 */
unsigned int Mesh::get_num_vertices() const {
    return m_num_vertices;
}

/* dump_vertices
 */
void Mesh::dump_vertices() {
    for (int i = 0; i < m_vertices.size(); i++) {
        std::cout << m_vertices[i].vertex.x << ", " << m_vertices[i].vertex.y << ", " << m_vertices[i].vertex.z << "," << std::endl;
    }
    std::cout << std::endl;
}

/* dump_normals
 */
void Mesh::dump_normals() {
    for (int i = 0; i < m_vertices.size(); i++) {
        std::cout << m_vertices[i].normal.x << ", " << m_vertices[i].normal.y << ", " << m_vertices[i].normal.z << "," << std::endl;
    }
    std::cout << std::endl;
}