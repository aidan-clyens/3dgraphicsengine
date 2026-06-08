#pragma once

#include <string>


unsigned char *load_image_data(const std::string &path, int *width, int *height, int *num_channels);

void free_image_data(unsigned char *data);

int write_png(const std::string &filename, int w, int h, int comp, const void *data, int stride_in_bytes);