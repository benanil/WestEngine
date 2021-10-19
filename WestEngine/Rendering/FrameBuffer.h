#pragma once
#include "glad.h"
#include "Common.h"

namespace WestEngine
{
	class FrameBuffer
	{
		uint handle;
		uint depthHandle;
		void Dispose();
	public:
		uint texture;
		int width; int height;
		
		FrameBuffer(const int& width, const int& height);
		~FrameBuffer();
		void Bind() const;
		void Invalidate(const int& width, const int& height);
		static void UnBind();
	};
}

