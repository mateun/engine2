#include "../external/stb_image.h"
#include "ImageLoader.h"

#include <fstream>
#include <iostream>

bool ImageLoader::Load(const std::string& filename, ImageData& outImage) {
    int w, h, c;
    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &c, 0);
    if (!data) return false;
    outImage.width = w;
    outImage.height = h;
    outImage.channels = c;
    outImage.pixels.assign(data, data + (w * h * c));
    stbi_image_free(data);
    return true;
}

bool ImageLoader::LoadGLBModel(const char* filename) {
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err, warn;
    bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
    if (!warn.empty()) {
        std::cout << "tinygltf warning: " << warn << std::endl;
    }
    if (!err.empty()) {
        std::cerr << "tinygltf error: " << err << std::endl;
    }
    if (!ret) {
        std::cerr << "Failed to load GLB: " << filename << std::endl;
        return false;
    }
    std::cout << "Loaded GLB: " << filename << std::endl;
    std::cout << "Meshes: " << model.meshes.size() << std::endl;
    std::cout << "Materials: " << model.materials.size() << std::endl;
    return true;
} 