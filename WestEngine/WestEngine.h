#pragma once
#include "Event.h"
namespace WestEngine
{
	class __declspec(dllexport) Engine
	{
	public:
		int windowWidth;
		int windowHeight;
		Sharp::Event<void> OnUpdate;
		void Run();
	};
}

