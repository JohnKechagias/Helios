#pragma once

#include "hlWindow.hpp"
#include "hlDevice.hpp"
#include "hlSwapChain.hpp"

#include <cassert>
#include <memory>
#include <vector>

namespace Helios {

    class HlRenderer {
        public:
        HlRenderer(HlWindow &window, HlDevice &device);
        ~HlRenderer();

        HlRenderer(const HlRenderer &) = delete;
        HlRenderer &operator=(const HlRenderer &) = delete;

        bool isFrameInProgress() const { return m_IsFrameStarted; }
        VkRenderPass getSwapChainRenderPass() const { return m_SwapChain->getRenderPass(); }

        VkCommandBuffer getCurrentCommandBuffer() const {
            assert(!m_IsFrameStarted && "Cannot get command buffer when frame not in progress");
            return m_CommandBuffers[m_CurrentImageIndex];
        }

        int getFrameIndex() const {
            assert(m_IsFrameStarted && "Cannot get frame index when frame not in progress");
            return m_CurrentFrameIndex;
        }

        VkCommandBuffer beginFrame();
        void endFrame();

        void beginSwapChainRenderPass(VkCommandBuffer VkCommandBuffer);
        void endSwapChainRenderPass(VkCommandBuffer VkCommandBuffer);

        private:
        void createCommandBuffers();
        void freeCommandBuffers();
        void recreateSwapChain();

        HlWindow &m_Window;
        HlDevice &m_Device;
        std::unique_ptr<HlSwapChain> m_SwapChain;
        std::vector<VkCommandBuffer> m_CommandBuffers;

        uint32_t m_CurrentImageIndex;
        int m_CurrentFrameIndex{0};
        bool m_IsFrameStarted;

        uint32_t m_CommandBuffersCount{HlSwapChain::MAX_FRAMES_IN_FLIGHT};
    };
}