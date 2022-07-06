#include "App.hpp"

namespace Helios {

    void VoxApp::run() {
        mainLoop();
    }

    void VoxApp::mainLoop() {
        while(!m_Window.shouldClose()) {

            glfwPollEvents();
        }
    }
}