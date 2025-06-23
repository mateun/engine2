#include "SceneNode.h"
#include <glm/gtc/matrix_transform.hpp>
#include "VulkanApp.h"

void SceneNode::add_child(std::unique_ptr<SceneNode> child) {
    children.push_back(std::move(child));
}

void SceneNode::render(VkCommandBuffer cmd, const glm::mat4& parentTransform) {
    glm::mat4 local = glm::translate(glm::mat4(1.0f), position);
    // For simplicity, only Y rotation for now
    local = glm::rotate(local, rotation.y, glm::vec3(0, 1, 0));
    local = glm::scale(local, scale);
    glm::mat4 world = parentTransform * local;
    // TODO: Pass world matrix to shader if needed
    if (mesh) {
        mesh->bind(cmd);
        mesh->draw(cmd);
    }
    for (auto& child : children) {
        child->render(cmd, world);
    }
} 