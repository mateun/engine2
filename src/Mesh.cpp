#include "Mesh.h"
#include <cstring>
#include <stdexcept>

namespace {
void create_buffer(VkDevice device, VkPhysicalDevice physicalDevice, VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    VkBufferCreateInfo bufferInfo{};
    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferInfo.size = size;
    bufferInfo.usage = usage;
    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS)
        throw std::runtime_error("Failed to create buffer");
    VkMemoryRequirements memRequirements;
    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);
    VkMemoryAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocInfo.allocationSize = memRequirements.size;
    VkPhysicalDeviceMemoryProperties memProperties;
    vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);
    for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
        if ((memRequirements.memoryTypeBits & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            allocInfo.memoryTypeIndex = i;
            break;
        }
    }
    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
        throw std::runtime_error("Failed to allocate buffer memory");
    vkBindBufferMemory(device, buffer, bufferMemory, 0);
}
}

Mesh::Mesh(VkDevice device, VkPhysicalDevice physicalDevice, const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    : device_(device), physicalDevice_(physicalDevice), index_count_(indices.size()) {
    create_vertex_buffer(vertices);
    create_index_buffer(indices);
}

Mesh::~Mesh() {
    if (vertex_buffer_ != VK_NULL_HANDLE) vkDestroyBuffer(device_, vertex_buffer_, nullptr);
    if (vertex_memory_ != VK_NULL_HANDLE) vkFreeMemory(device_, vertex_memory_, nullptr);
    if (index_buffer_ != VK_NULL_HANDLE) vkDestroyBuffer(device_, index_buffer_, nullptr);
    if (index_memory_ != VK_NULL_HANDLE) vkFreeMemory(device_, index_memory_, nullptr);
}

Mesh::Mesh(Mesh&& other) noexcept {
    *this = std::move(other);
}

Mesh& Mesh::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        device_ = other.device_;
        physicalDevice_ = other.physicalDevice_;
        vertex_buffer_ = other.vertex_buffer_;
        vertex_memory_ = other.vertex_memory_;
        index_buffer_ = other.index_buffer_;
        index_memory_ = other.index_memory_;
        index_count_ = other.index_count_;
        other.vertex_buffer_ = VK_NULL_HANDLE;
        other.vertex_memory_ = VK_NULL_HANDLE;
        other.index_buffer_ = VK_NULL_HANDLE;
        other.index_memory_ = VK_NULL_HANDLE;
        other.index_count_ = 0;
    }
    return *this;
}

void Mesh::create_vertex_buffer(const std::vector<Vertex>& vertices) {
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
    create_buffer(device_, physicalDevice_, bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertex_buffer_, vertex_memory_);
    void* data;
    vkMapMemory(device_, vertex_memory_, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(device_, vertex_memory_);
}

void Mesh::create_index_buffer(const std::vector<uint32_t>& indices) {
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
    create_buffer(device_, physicalDevice_, bufferSize, VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, index_buffer_, index_memory_);
    void* data;
    vkMapMemory(device_, index_memory_, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(device_, index_memory_);
}

void Mesh::bind(VkCommandBuffer cmdBuffer) const {
    if (vertex_buffer_ == VK_NULL_HANDLE) {
        printf("[Mesh::bind] vertex_buffer_ is VK_NULL_HANDLE, skipping bind.\n");
        return;
    }
    VkBuffer vertexBuffers[] = { vertex_buffer_ };
    VkDeviceSize offsets[] = { 0 };
    vkCmdBindVertexBuffers(cmdBuffer, 0, 1, vertexBuffers, offsets);
    if (index_buffer_ != VK_NULL_HANDLE) {
        vkCmdBindIndexBuffer(cmdBuffer, index_buffer_, 0, VK_INDEX_TYPE_UINT32);
    } else {
        printf("[Mesh::bind] index_buffer_ is VK_NULL_HANDLE, not binding index buffer.\n");
    }
}

void Mesh::draw(VkCommandBuffer cmdBuffer) const {
    if (index_buffer_ != VK_NULL_HANDLE && index_count_ > 0) {
        vkCmdDrawIndexed(cmdBuffer, static_cast<uint32_t>(index_count_), 1, 0, 0, 0);
        printf("[Mesh::draw] Drawing mesh with %zu indices.\n", index_count_);
    } else {
        printf("[Mesh::draw] index_buffer_ is VK_NULL_HANDLE or index_count_ == 0, skipping draw.\n");
    }
} 