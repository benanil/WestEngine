#pragma once
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

namespace WestEngine
{
	class Device
	{
	public:
		static void Create();
		/// <summary>
		/// Get Monitors Size by pixel
		/// </summary>
		/// <param name="index">monitor index</param>
		static const glm::vec2& GetMonitorScale();
	};
}

