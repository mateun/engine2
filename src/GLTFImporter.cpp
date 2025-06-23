#include "../external/stb_image_write.h"
#define TINYGLTF_IMPLEMENTATION
#include "GLTFImporter.h"
#include <iostream>

bool GLTFImporter::LoadGLB(const std::string& filename) {
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

bool GLTFImporter::LoadMesh(const std::string& filename, std::vector<Vertex>& outVertices, std::vector<uint32_t>& outIndices) {
    tinygltf::Model model;
    tinygltf::TinyGLTF loader;
    std::string err, warn;
    bool ret = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
    if (!ret) {
        std::cerr << "Failed to load GLB: " << filename << std::endl;
        return false;
    }
    if (model.meshes.empty()) {
        std::cerr << "No meshes in GLB: " << filename << std::endl;
        return false;
    }
    const tinygltf::Mesh& mesh = model.meshes[0];
    if (mesh.primitives.empty()) {
        std::cerr << "No primitives in mesh." << std::endl;
        return false;
    }
    const tinygltf::Primitive& primitive = mesh.primitives[0];
    // Positions
    const float* positions = nullptr;
    const float* colors = nullptr;
    const float* uvs = nullptr;
    size_t vertexCount = 0;
    // POSITION
    {
        auto it = primitive.attributes.find("POSITION");
        if (it == primitive.attributes.end()) {
            std::cerr << "No POSITION attribute." << std::endl;
            return false;
        }
        const tinygltf::Accessor& accessor = model.accessors[it->second];
        const tinygltf::BufferView& view = model.bufferViews[accessor.bufferView];
        positions = reinterpret_cast<const float*>(&model.buffers[view.buffer].data[view.byteOffset + accessor.byteOffset]);
        vertexCount = accessor.count;
    }
    // COLOR_0 (optional)
    {
        auto it = primitive.attributes.find("COLOR_0");
        if (it != primitive.attributes.end()) {
            const tinygltf::Accessor& accessor = model.accessors[it->second];
            const tinygltf::BufferView& view = model.bufferViews[accessor.bufferView];
            colors = reinterpret_cast<const float*>(&model.buffers[view.buffer].data[view.byteOffset + accessor.byteOffset]);
        }
    }
    // TEXCOORD_0 (optional)
    {
        auto it = primitive.attributes.find("TEXCOORD_0");
        if (it != primitive.attributes.end()) {
            const tinygltf::Accessor& accessor = model.accessors[it->second];
            const tinygltf::BufferView& view = model.bufferViews[accessor.bufferView];
            uvs = reinterpret_cast<const float*>(&model.buffers[view.buffer].data[view.byteOffset + accessor.byteOffset]);
        }
    }
    // Indices
    outVertices.clear();
    outIndices.clear();
    for (size_t i = 0; i < vertexCount; ++i) {
        Vertex v{};
        v.pos[0] = positions[i * 3 + 0];
        v.pos[1] = positions[i * 3 + 1];
        // Z is ignored for now
        if (colors) {
            v.color[0] = colors[i * 3 + 0];
            v.color[1] = colors[i * 3 + 1];
            v.color[2] = colors[i * 3 + 2];
        } else {
            v.color[0] = v.color[1] = v.color[2] = 1.0f;
        }
        if (uvs) {
            v.uv[0] = uvs[i * 2 + 0];
            v.uv[1] = uvs[i * 2 + 1];
        } else {
            v.uv[0] = v.uv[1] = 0.0f;
        }
        outVertices.push_back(v);
    }
    // Indices
    if (primitive.indices >= 0) {
        const tinygltf::Accessor& accessor = model.accessors[primitive.indices];
        const tinygltf::BufferView& view = model.bufferViews[accessor.bufferView];
        const unsigned char* data = &model.buffers[view.buffer].data[view.byteOffset + accessor.byteOffset];
        for (size_t i = 0; i < accessor.count; ++i) {
            uint32_t idx = 0;
            switch (accessor.componentType) {
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE: idx = data[i]; break;
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT: idx = ((const uint16_t*)data)[i]; break;
                case TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT: idx = ((const uint32_t*)data)[i]; break;
                default: break;
            }
            outIndices.push_back(idx);
        }
    } else {
        // No indices, use sequential
        for (uint32_t i = 0; i < (uint32_t)vertexCount; ++i) outIndices.push_back(i);
    }
    return true;
} 