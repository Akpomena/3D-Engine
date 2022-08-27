#pragma once
#include "VertexBuffer.h"

class VertexBufferLayout;

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(VertexBuffer& buffer, VertexBufferLayout& layout);
	void bind();
	void unbind();
private:
	unsigned int m_RendererID;
};

