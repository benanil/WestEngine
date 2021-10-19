#pragma once
#include "Common.h"
#include "Renderer.h"

namespace WestEngine
{
	class __declspec(dllexport) Engine
	{
	public:
		static float sunAngle;
		static int WindowWidth;
		static int WindowHeight;
		static ShaderProperties properties;

		static Eventi OnFocus;
		static Event OnUpdate;
		static Event OnEditor;

		void Run();
	};
}

