#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace Helios {

    class HlWindow {
        public:
        HlWindow(int width, int height, std::string name);
        ~HlWindow();

        HlWindow(const HlWindow&) = delete;
        HlWindow &operator=(const HlWindow&) = delete;

        inline bool shouldClose() { return glfwWindowShouldClose(m_Window); }
        void createWindowSurface(VkInstance instance, VkSurfaceKHR* surface);
        VkExtent2D getExtent() { return {static_cast<uint32_t>(m_Width), static_cast<uint32_t>(m_Height)}; }
        VkExtent2D getWindowsFramebufferSize();

        bool wasWindowResized() { return m_FramebufferResized; }
        void resetWindowResizedFlag() { m_FramebufferResized  = false; }
        
        private:
        static void framebufferResizeCallback(GLFWwindow *window, int width, int height);
        void initWindow();

        int m_Width;
        int m_Height;
        bool m_FramebufferResized = false;

        std::string m_WindowName;
        GLFWwindow* m_Window;
    };

} // namespace Helios