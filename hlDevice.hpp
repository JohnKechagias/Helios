#pragma once

#include "hlWindow.hpp"
#include "hlDebugMessenger.hpp"
#include "hlExtensionsManager.hpp"
#include "hlCommandQueues.hpp"

#include <iosfwd>
#include <cstdlib>

#include <cstring>

namespace Helios {

    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };

    class HlDevice {
        public:
        HlDevice(HlWindow& window);
        ~HlDevice();

        // Not copyable or movable
        HlDevice(const HlDevice &) = delete;
        void operator=(const HlDevice &) = delete;
        HlDevice(HlDevice &&) = delete;
        HlDevice &operator=(HlDevice &&) = delete;

        VkCommandPool getCommandPool() { return m_CommandPool; }
        VkDevice device() { return m_Device; } 
        VkSurfaceKHR surface() { return m_Surface; }
        VkQueue graphicsQueue() { return m_Queues.graphicsQueue; }
        VkQueue presentQueue() { return m_Queues.presentQueue; }

        SwapChainSupportDetails getSwapChainSupport() { return querySwapChainSupport(m_PhysicalDevice); }
        QueueFamilyIndices findPhysicalQueueFamilies() { return findQueueFamilies(m_PhysicalDevice); }
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        VkFormat findSupportedFormat(const std::vector<VkFormat> &candidates, VkImageTiling tiling, VkFormatFeatureFlags features);

        void createBuffer(
            VkDeviceSize size,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkBuffer &buffer,
            VkDeviceMemory &bufferMemory);
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount);

        void createImageWithInfo(
            const VkImageCreateInfo &imageInfo,
            VkMemoryPropertyFlags properties,
            VkImage &image,
            VkDeviceMemory &imageMemory);

        VkPhysicalDeviceProperties properties;

        private:
        void createInstance();
        void destroyInstance();

        void createSurface();
        void destroySurface();

        void setupDebugMessenger();
        void destroyDebugMessenger();

        void pickPhysicalDevice();

        void createLogicalDevice();
        void destroyLogicalDevice();

        void createCommandPool();

        bool checkValidationLayerSupport();

        // helper functions
        bool isDeviceSuitable(VkPhysicalDevice device);
        int gradePhysicalDevice(VkPhysicalDevice device);
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

        VkInstance m_Instance;
        HlDebugMessenger m_DebugMessenger;
        VkPhysicalDevice m_PhysicalDevice;
        HlWindow &m_Window;
        VkCommandPool m_CommandPool;

        VkDevice m_Device;
        VkSurfaceKHR m_Surface;
        HlCommandQueues m_Queues{};

        const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};
    };
}