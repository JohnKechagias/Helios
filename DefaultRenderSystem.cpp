#include "DefaultRenderSystem.hpp"

#include "hlRenderer.hpp"

#include <fstream>
#include <cassert>


namespace Helios {

    DefaultRenderSystem::DefaultRenderSystem(HlDevice& device, VkRenderPass renderPass) : m_Device{device} {
        createPipelineLayout();
        createPipeline(renderPass);
    }

    DefaultRenderSystem::~DefaultRenderSystem() {
        vkDestroyPipelineLayout(m_Device.device(), m_PipelineLayout, nullptr);
    }

    void DefaultRenderSystem::createPipelineLayout() {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0; // Optional
        pipelineLayoutInfo.pSetLayouts = nullptr; // Optional
        pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
        pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

        if (vkCreatePipelineLayout(m_Device.device(), &pipelineLayoutInfo, nullptr, &m_PipelineLayout) != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }
    }
    
    void DefaultRenderSystem::createPipeline(VkRenderPass renderPass) {
        assert(m_PipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

        PipelineConfigInfo pipelineConfig{};
        HlPipeline::defaultPipelineConfigInfo(pipelineConfig);
        pipelineConfig.renderPass = renderPass;
        pipelineConfig.pipelineLayout = m_PipelineLayout;

        m_Pipeline = std::make_unique<HlPipeline>(
            m_Device,
            "shaders/defaultShader.vert.spv",
            "shaders/defaultShader.frag.spv",
            pipelineConfig
        );
    }
}