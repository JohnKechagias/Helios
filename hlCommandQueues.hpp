#pragma once

#include <optional>
#include <vulkan/vulkan.h>
#include <vector>


namespace Helios {

    struct QueueFamilyIndices {
        /* We use std::optional in order to distinguish between
        queue families that are available and have been found
        and queue families that aren't available and couldn't
        be found. If a graphicsFamily doesn't have a value, it 
        means that the specified queue family couldn't be found.
        Either its not supported by the graphics card or
        something else that I'm unaware of. */

        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;
        std::optional<uint32_t> transferFamily;

        inline bool isComplete() { return graphicsFamily.has_value()
            && presentFamily.has_value() && transferFamily.has_value(); }
    };

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR surface);

    struct HlCommandQueues {
        public:
        VkQueue presentQueue;
        VkQueue graphicsQueue;
        VkQueue transferQueue;
    };
}