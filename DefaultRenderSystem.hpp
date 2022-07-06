#pragma once

#include "hlPipeline.hpp"

// std
#include <memory>
#include <vector>

namespace Helios {

    class DefaultRenderSystem {
        public:
        DefaultRenderSystem(HlDevice& device, VkRenderPass renderPass);
        ~DefaultRenderSystem();

        DefaultRenderSystem(const DefaultRenderSystem &) = delete;
        DefaultRenderSystem &operator=(const DefaultRenderSystem &) = delete;

        private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        HlDevice& m_Device;

        std::unique_ptr<HlPipeline> m_Pipeline;
        VkPipelineLayout m_PipelineLayout;
    };
}