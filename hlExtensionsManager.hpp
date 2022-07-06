#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <set>

namespace Helios {

    extern const bool enableValidationLayers;

    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    class HlExtensionsManager {
        public:
        static std::vector<const char*> getRequiredInstanceExtensions();
        static void listAvailableInstanceExtensions();

        static bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        static void listAvailableDeviceExtensions(VkPhysicalDevice device);
    };
}