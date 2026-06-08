#include "TextureCubeMap.h"


#include <iostream>

/* TextureCubeMap
 */
TextureCubeMap::TextureCubeMap() {

}

/* load
 */
void TextureCubeMap::load(std::vector<std::string> faces_files_paths) {
    int texture_width, texture_height, num_channels;
    std::vector<unsigned char *> faces;

    for (int i = 0; i < faces_files_paths.size(); i++) {
        unsigned char *texture_data = load_image_data(faces_files_paths[i], &texture_width, &texture_height, &num_channels);
        faces.push_back(texture_data);
    }

    this->load(faces, texture_width, texture_height, num_channels);

    for (int i = 0; i < faces_files_paths.size(); i++) {
        free_image_data((unsigned char *)faces[i]);
    }
}

/* load
 */
void TextureCubeMap::load(std::vector<unsigned char*> faces, int width, int height, int num_channels) {
    m_texture_width = width;
    m_texture_height = height;
    m_num_channels = num_channels;

    Texture::load(faces.data(), GL_TEXTURE_CUBE_MAP);

    glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture_id);

    GLenum format;
    if (m_num_channels == 1) {
        format = GL_RED;
    }
    else if (m_num_channels == 3) {
        format = GL_RGB;
    }
    else if (m_num_channels == 4) {
        format = GL_RGBA;
    }

    for (int i = 0; i < faces.size(); i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, m_texture_width, m_texture_height, 0, format, GL_UNSIGNED_BYTE, faces[i]);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAX_LEVEL, 0);
}