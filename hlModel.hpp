#pragma once

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include "hlDevice.hpp"

#include <vector>

namespace Helios {


class HlModel {
    public:
    struct Vertex {
        glm::vec3 position{};
        glm::vec3 color{};
    
        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
    };

    HlModel(HlDevice &device, const std::vector<Vertex> &vertices);
    ~HlModel();

    HlModel(const HlDevice &) = delete;
    HlModel &operator=(const HlModel &) = delete;

    void bind(VkCommandBuffer VkCommandBuffer);
    void draw(VkCommandBuffer VkCommandBuffer);

    private:
    void createVertexBuffers(const std::vector<Vertex> &vertices);

    HlDevice &m_Device;
    VkBuffer m_VertexBuffer;
    VkDeviceMemory m_VertexBufferMemory;
    uint32_t m_VertexCount;
};
/*
const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};
*/
}