#include "LoadImage.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb_image.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif
#include "stb_image_write.h"


unsigned char *load_image_data(const std::string &path, int *width, int *height, int *num_channels) {
    return stbi_load(path.c_str(), width, height, num_channels, 0);
}

void free_image_data(unsigned char *data) {
    stbi_image_free(data);
}


int write_png(const std::string &filename, int w, int h, int comp, const void *data, int stride_in_bytes) {
    return stbi_write_png(filename.c_str(), w, h, comp, data, stride_in_bytes);
}