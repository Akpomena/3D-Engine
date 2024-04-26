#include "FrameBuffer.h"
#include <iostream>
#include <glad/glad.h>

Engine::FrameBuffer::FrameBuffer(FrameBufferProp prop)
{
	m_Prop = prop;

	glGenFramebuffers(1, &m_FrameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);

	glGenTextures(1, &m_TextureColourBuffer);
	glBindTexture(GL_TEXTURE_2D, m_TextureColourBuffer);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Prop.Width, m_Prop.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TextureColourBuffer, 0);

	if (m_Prop.IsDepthBuffer)
	{
		// create render buffer object
		glGenRenderbuffers(1, &m_RenderBufferObject);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferObject);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Prop.Width, m_Prop.Height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferObject);
	}

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Engine::FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &m_FrameBuffer);
}

void Engine::FrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer);
}

void Engine::FrameBuffer::UnBind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Engine::FrameBuffer::UpdateBufferSize(int width, int height)
{
	glBindTexture(GL_TEXTURE_2D, m_TextureColourBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_Prop.IsDepthBuffer)
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferObject);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}
