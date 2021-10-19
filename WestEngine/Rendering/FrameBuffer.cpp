#include "FrameBuffer.h"

namespace WestEngine
{
	FrameBuffer::FrameBuffer(const int& width, const int& height) {
		Invalidate(width, height);
	}

	FrameBuffer::~FrameBuffer() {
		Dispose();
	}

	void FrameBuffer::Invalidate(const int& width, const int& height) {
		handle = 0;
		texture = 0;
		depthHandle = 0;

		glGenFramebuffers(1, &handle);
		glBindFramebuffer(GL_FRAMEBUFFER, handle);

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, (const void*)0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glFramebufferTexture2D(handle, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

		glGenTextures(1, &depthHandle);
		glBindTexture(GL_TEXTURE_2D, depthHandle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, (const void*)0);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthHandle, 0);
	}

	void FrameBuffer::Bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, handle);
		glViewport(0, 0, width, height);
	}
	
	void FrameBuffer::UnBind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void FrameBuffer::Dispose() {
		glDeleteFramebuffers(1, &handle);
		glDeleteTextures(2, &texture);
	}
}