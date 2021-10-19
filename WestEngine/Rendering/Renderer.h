#pragma once
#include "Common.h"
#include "Renderer.h"
#include <list>

namespace WestEngine
{
	class Renderer
	{
		std::list<Mesh> meshes;
	public:
		static void Render();
	};
}