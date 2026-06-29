#pragma once

// Includes
#include "Types.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>

class Renderer;

/* Texture
 */
class Texture {
    friend class Renderer;

    public:
        Texture();
        virtual ~Texture();

        void load(unsigned int texture_type);
        void load(const std::string &texture_path, unsigned int texture_type);
        void load(void *data, unsigned int texture_type);

        void enable(int index = 0);
        void disable();

        unsigned int get_texture_type() const;
        int get_width() const;
        int get_height() const;

        unsigned int get_texture_id() const;

    protected:
        void free_data();

        unsigned int m_texture_id;
        unsigned int m_texture_type;

        int m_texture_width;
        int m_texture_height;
        int m_num_channels;

        void *p_data;
};