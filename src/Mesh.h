#pragma once
#include <vulkan/vulkan.h>
#include <vector>

struct Vertex {
    float pos[2];
    float color[3];
    float uv[2];
};

class Mesh {
public:
    Mesh(VkDevice device, VkPhysicalDevice physicalDevice,
         const std::vector<Vertex>& vertices,
         const std::vector<uint32_t>& indices);
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    void bind(VkCommandBuffer cmdBuffer) const;
    void draw(VkCommandBuffer cmdBuffer) const;
    size_t index_count() const { return index_count_; }

private:
    void create_vertex_buffer(const std::vector<Vertex>& vertices);
    void create_index_buffer(const std::vector<uint32_t>& indices);

    VkDevice device_ = VK_NULL_HANDLE;
    VkPhysicalDevice physicalDevice_ = VK_NULL_HANDLE;
    VkBuffer vertex_buffer_ = VK_NULL_HANDLE;
    VkDeviceMemory vertex_memory_ = VK_NULL_HANDLE;
    VkBuffer index_buffer_ = VK_NULL_HANDLE;
    VkDeviceMemory index_memory_ = VK_NULL_HANDLE;
    size_t index_count_ = 0;
}; 