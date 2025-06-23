#pragma once
#include "../external/tiny_gltf.h"
#include <string>
#include <vector>
#include "VulkanApp.h" // for Vertex

class GLTFImporter {
public:
    // Loads a .glb file and prints basic info. Returns true on success.
    static bool load_glb(const std::string& filename);
    // Loads the first mesh from a .glb file into vertices and indices. Returns true on success.
    static bool load_mesh(const std::string& filename, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices);
}; 