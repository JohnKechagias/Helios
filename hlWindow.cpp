#include "hlWindow.hpp"

#include <stdexcept>

namespace Helios {

    HlWindow::HlWindow(int width, int height, std::string name)
        : m_Width(width), m_Height(height), m_WindowName(name) {
        initWindow();
    }

    HlWindow::~HlWindow() {
        glfwDestroyWindow(m_Window);
    }

    void HlWindow::initWindow() {
        glfwInit();
        // Tell GLFW to not create an OpenGL Context
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        // Disable window resize
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        
        m_Window = glfwCreateWindow(m_Width, m_Height, m_WindowName.c_str(), nullptr, nullptr);
    }

    void HlWindow::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, m_Window, NULL, surface))
        {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    void HlWindow::framebufferResizeCallback(GLFWwindow *window, int width, int height) {
        auto hlWindow = reinterpret_cast<HlWindow *>(glfwGetWindowUserPointer(window));
        hlWindow->m_FramebufferResized = true;
        hlWindow->m_Width = width;
        hlWindow->m_Height = height;
    }
}