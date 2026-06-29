#pragma once

// Includes
#include "Types.h"
#include "Texture.h"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>


/* Texture2D
 */
class Texture2D : public Texture {
    public:
        Texture2D();

        void load(const std::string &texture_path);
        void load(unsigned char *data, int width, int height, int num_channels);

    private:
        void _load();
};