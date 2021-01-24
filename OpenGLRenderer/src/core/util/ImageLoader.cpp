#include "pch.h"
#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

unsigned char* ImageLoader::loadImage(std::string src, int* w, int* h, int* n) {
    return stbi_load(src.c_str(), w, h, n, 4);
}

void ImageLoader::Clear(unsigned char* d) {
    stbi_image_free(d);
}
