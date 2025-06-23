#pragma once
#include <string>
#include <vector>
#include "../external/tiny_gltf.h"

class ImageLoader {
public:
    struct ImageData {
        int width = 0;
        int height = 0;
        int channels = 0;
        std::vector<unsigned char> pixels;
    };

    // Loads an image from file. Returns true on success.
    static bool Load(const std::string& filename, ImageData& outImage);

    // Loads a .glb file and prints basic info. Returns true on success.
    static bool LoadGLBModel(const char* filename);
}; 