#pragma once
#include <memory>
#include "SceneNode.h"

class VulkanApp;

class Scene {
public:
    std::unique_ptr<SceneNode> root;
    void render(VkCommandBuffer cmd) {
        if (root) root->render(cmd);
    }
}; 