#pragma once

// Includes
#include "Types.h"
#include "LoadImage.h"
#include "Texture.h"

#include <vector>


/* TextureCubeMap
 */
class TextureCubeMap : public Texture {
    public:
        TextureCubeMap();

        void load(std::vector<std::string> faces_files_paths);
        void load(std::vector<unsigned char*> faces, int width, int height, int num_channels);
};