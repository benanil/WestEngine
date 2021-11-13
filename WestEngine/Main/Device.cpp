
#include "Device.h"
#include <iostream>

namespace WestEngine {
    
    /// primary monitor size
    static 
        
        
        vec2 MonitorScale = Math::vec2(0,0);

    void Device::Create() {
        const GLFWvidmode* vidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        MonitorScale.x = vidMode->width;
        MonitorScale.y = vidMode->height;
        std::cout << "monitor size: " << vidMode->width << " " << vidMode->height << std::endl;
    }

    /// <summary>
    /// Gets Primary Window Scame
    /// </summary>
    const Math::vec2& Device::GetMonitorScale()
    {
        return MonitorScale;
    }
}

