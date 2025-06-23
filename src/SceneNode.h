#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Mesh.h"
// #include "VulkanApp.h" // Remove this include

class VulkanApp; // Forward declaration

class SceneNode {
public:
    glm::vec3 position{0.0f}, rotation{0.0f}, scale{1.0f, 1.0f, 1.0f};
    std::shared_ptr<Mesh> mesh;
    std::vector<std::unique_ptr<SceneNode>> children;

    void add_child(std::unique_ptr<SceneNode> child);
    void render(VkCommandBuffer cmd, const glm::mat4& parentTransform = glm::mat4(1.0f));
}; 