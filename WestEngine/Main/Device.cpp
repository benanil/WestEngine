
#include "Device.h"
#include <iostream>

namespace WestEngine {
    
    /// primary monitor size
    static glm::vec2 MonitorScale = glm::vec2(0,0);

    void Device::Create() {
        const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        MonitorScale.x = vidMode->width;
        MonitorScale.y = vidMode->height;
        std::cout << "monitor size: " << vidMode->width << " " << vidMode->height << std::endl;
    }

    /// <summary>
    /// Gets Primary Window Scame
    /// </summary>
    const glm::vec2& Device::GetMonitorScale()
    {
        return MonitorScale;
    }
}

