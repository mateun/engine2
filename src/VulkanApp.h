#pragma once

#include <vulkan/vulkan.h>
#include <windows.h>
#include <vector>
#include <memory>
#include "Camera.h"
#include <string>
#include "Mesh.h"
#include "Scene.h"

class VulkanApp {
public:
    VulkanApp(HINSTANCE hInstance, HWND hwnd, uint32_t width, uint32_t height);
    ~VulkanApp();
    void DrawFrame();
    void WaitDeviceIdle();
    // Draw API
    void DrawQuad(float x, float y, float width, float height, const float color[3]);
    // Draws a mesh from vertices and indices
    // void DrawMesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    void set_camera(const Camera& camera);
    void set_scene(Scene* scene);
    void RecordDrawCommands();
    VkDevice device() const { return device_; }
    VkPhysicalDevice physical_device() const { return physicalDevice_; }
    VkCommandBuffer current_command_buffer() const { return commandBuffers_[currentFrame_]; }

private:
    void InitVulkan(HINSTANCE hInstance, HWND hwnd, uint32_t width, uint32_t height);
    void Cleanup();
    void CreateInstance();
    void CreateSurface(HINSTANCE hInstance, HWND hwnd);
    void PickPhysicalDevice();
    void CreateLogicalDevice();
    void CreateSwapchain(uint32_t width, uint32_t height);
    void CreateImageViews();
    void CreateRenderPass();
    void CreateFramebuffers();
    void CreateCommandPool();
    void CreateCommandBuffers();
    void CreateSyncObjects();
    // New for drawing
    void CreateGraphicsPipeline();
    // Validation layers
    const std::vector<const char*> validationLayers_ = { "VK_LAYER_KHRONOS_validation" };
    bool enableValidationLayers_ = true;
    VkDebugUtilsMessengerEXT debugMessenger_ = VK_NULL_HANDLE;
    void setup_debug_messenger();
    void destroy_debug_messenger();

    // Add missing function declarations
    void CreateDescriptorSetLayout();
    void CreateTextureImage();
    void CreateTextureImageView();
    void CreateTextureSampler();
    void CreateDescriptorPool();
    void CreateDescriptorSet();

    VkInstance instance_ = VK_NULL_HANDLE;
    VkSurfaceKHR surface_ = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    VkQueue graphicsQueue_ = VK_NULL_HANDLE;
    VkQueue presentQueue_ = VK_NULL_HANDLE;
    VkSwapchainKHR swapchain_ = VK_NULL_HANDLE;
    std::vector<VkImage> swapchainImages_;
    std::vector<VkImageView> swapchainImageViews_;
    VkFormat swapchainImageFormat_;
    VkExtent2D swapchainExtent_;
    VkRenderPass renderPass_ = VK_NULL_HANDLE;
    std::vector<VkFramebuffer> swapchainFramebuffers_;
    VkCommandPool commandPool_ = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> commandBuffers_;
    std::vector<VkSemaphore> imageAvailableSemaphores_;
    std::vector<VkSemaphore> renderFinishedSemaphores_;
    std::vector<VkFence> inFlightFences_;
    size_t currentFrame_ = 0;
    const int MAX_FRAMES_IN_FLIGHT = 2;
    bool framebufferResized_ = false;
    // Drawing resources
    VkPipelineLayout pipelineLayout_ = VK_NULL_HANDLE;
    VkPipeline graphicsPipeline_ = VK_NULL_HANDLE;
    VkBuffer vertexBuffer_ = VK_NULL_HANDLE;
    VkDeviceMemory vertexBufferMemory_ = VK_NULL_HANDLE;
    std::vector<Vertex> quadVertices_;
    // Texture resources
    VkImage textureImage_ = VK_NULL_HANDLE;
    VkDeviceMemory textureImageMemory_ = VK_NULL_HANDLE;
    VkImageView textureImageView_ = VK_NULL_HANDLE;
    VkSampler textureSampler_ = VK_NULL_HANDLE;
    VkDescriptorSetLayout descriptorSetLayout_ = VK_NULL_HANDLE;
    VkDescriptorPool descriptorPool_ = VK_NULL_HANDLE;
    VkDescriptorSet descriptorSet_ = VK_NULL_HANDLE;
    Camera camera_;
    // MVP uniform buffer
    VkBuffer mvpBuffer_ = VK_NULL_HANDLE;
    VkDeviceMemory mvpBufferMemory_ = VK_NULL_HANDLE;
    VkDescriptorBufferInfo mvpBufferInfo_{};
    Scene* scene_ = nullptr;
}; 