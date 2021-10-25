#pragma once
#include "Common.h"

namespace WestEngine
{
	class FrameBuffer
	{
		unsigned int handle;
		unsigned int depthHandle;
		void Dispose();
	public:
		unsigned int texture;
		int width; int height;
		
		FrameBuffer(const int& width, const int& height);
		~FrameBuffer();
		void Bind() const;
		void Invalidate(const int& width, const int& height);
		static void UnBind();
	};
}

