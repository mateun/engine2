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
    void draw_frame();
    void wait_device_idle();
    // Draw API
    void draw_quad(float x, float y, float width, float height, const float color[3]);
    // Draws a mesh from vertices and indices
    // void draw_mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
    void set_camera(const Camera& camera);
    void set_scene(Scene* scene);
    void record_draw_commands();
    VkDevice device() const { return device_; }
    VkPhysicalDevice physical_device() const { return physical_device_; }
    VkCommandBuffer current_command_buffer() const { return command_buffers_[current_frame_]; }

private:
    void init_vulkan(HINSTANCE hInstance, HWND hwnd, uint32_t width, uint32_t height);
    void cleanup();
    void create_instance();
    void create_surface(HINSTANCE hInstance, HWND hwnd);
    void pick_physical_device();
    void create_logical_device();
    void create_swapchain(uint32_t width, uint32_t height);
    void create_image_views();
    void create_render_pass();
    void create_framebuffers();
    void create_command_pool();
    void create_command_buffers();
    void create_sync_objects();
    // New for drawing
    void create_graphics_pipeline();
    // Validation layers
    const std::vector<const char*> validation_layers_ = { "VK_LAYER_KHRONOS_validation" };
    bool enable_validation_layers_ = true;
    VkDebugUtilsMessengerEXT debug_messenger_ = VK_NULL_HANDLE;
    void setup_debug_messenger();
    void destroy_debug_messenger();

    // Add missing function declarations
    void create_descriptor_set_layout();
    void create_texture_image();
    void create_texture_image_view();
    void create_texture_sampler();
    void create_descriptor_pool();
    void create_descriptor_set();

    VkInstance instance_ = VK_NULL_HANDLE;
    VkSurfaceKHR surface_ = VK_NULL_HANDLE;
    VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    VkQueue graphics_queue_ = VK_NULL_HANDLE;
    VkQueue present_queue_ = VK_NULL_HANDLE;
    VkSwapchainKHR swapchain_ = VK_NULL_HANDLE;
    std::vector<VkImage> swapchain_images_;
    std::vector<VkImageView> swapchain_image_views_;
    VkFormat swapchain_image_format_;
    VkExtent2D swapchain_extent_;
    VkRenderPass render_pass_ = VK_NULL_HANDLE;
    std::vector<VkFramebuffer> swapchain_framebuffers_;
    VkCommandPool command_pool_ = VK_NULL_HANDLE;
    std::vector<VkCommandBuffer> command_buffers_;
    std::vector<VkSemaphore> image_available_semaphores_;
    std::vector<VkSemaphore> render_finished_semaphores_;
    std::vector<VkFence> in_flight_fences_;
    size_t current_frame_ = 0;
    const int max_frames_in_flight_ = 2;
    bool framebuffer_resized_ = false;
    // Drawing resources
    VkPipelineLayout pipeline_layout_ = VK_NULL_HANDLE;
    VkPipeline graphics_pipeline_ = VK_NULL_HANDLE;
    VkBuffer vertex_buffer_ = VK_NULL_HANDLE;
    VkDeviceMemory vertex_buffer_memory_ = VK_NULL_HANDLE;
    std::vector<Vertex> quad_vertices_;
    // Texture resources
    VkImage texture_image_ = VK_NULL_HANDLE;
    VkDeviceMemory texture_image_memory_ = VK_NULL_HANDLE;
    VkImageView texture_image_view_ = VK_NULL_HANDLE;
    VkSampler texture_sampler_ = VK_NULL_HANDLE;
    VkDescriptorSetLayout descriptor_set_layout_ = VK_NULL_HANDLE;
    VkDescriptorPool descriptor_pool_ = VK_NULL_HANDLE;
    VkDescriptorSet descriptor_set_ = VK_NULL_HANDLE;
    Camera camera_;
    // MVP uniform buffer
    VkBuffer mvp_buffer_ = VK_NULL_HANDLE;
    VkDeviceMemory mvp_buffer_memory_ = VK_NULL_HANDLE;
    VkDescriptorBufferInfo mvp_buffer_info_{};
    Scene* scene_ = nullptr;
}; 