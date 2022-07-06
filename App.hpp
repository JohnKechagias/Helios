#pragma once

#include "hlDevice.hpp"
#include "hlPipeline.hpp"
#include "hlSwapChain.hpp"

namespace Helios {

    static constexpr uint32_t WIDTH = 800;
    static constexpr uint32_t HEIGHT = 600;
    
    class VoxApp {
        public:
        void run();
        void mainLoop();

        private:
        HlWindow m_Window{WIDTH, HEIGHT, "Vulkan is my city"};
        HlDevice m_Engine{m_Window};
        HlSwapChain m_SwapChain{};
        HlPipeline m_Pipeline{
        m_Engine.m_Device, 
        "shaders/defaultShader.vert.spv",
        "shaders/defaultShader.frag.spv",
        HlPipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
    };
}