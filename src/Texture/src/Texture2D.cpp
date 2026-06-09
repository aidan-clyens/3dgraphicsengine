#include "Texture2D.h"


/* Texture2D
 */
Texture2D::Texture2D() {

}

/* load
 */
void Texture2D::load(const std::string &texture_path) {
    Texture::load(texture_path, GL_TEXTURE_2D);

    this->_load();
    this->free_data();
}

/* load
 */
void Texture2D::load(unsigned char *data, int width, int height, int num_channels) {
    m_texture_width = width;
    m_texture_height = height;
    m_num_channels = num_channels;

    Texture::load(data, GL_TEXTURE_2D);

    this->_load();
}

/* _load
 */
void Texture2D::_load() {
    if (p_data) {
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

        glBindTexture(GL_TEXTURE_2D, m_texture_id);
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_texture_width, m_texture_height, 0, format, GL_UNSIGNED_BYTE, (unsigned char*)p_data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
}