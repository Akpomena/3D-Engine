#include "VertexArray.h"
#include "VertexBufferLayout.h"

#include <glad/glad.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
	bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(VertexBuffer& buffer, VertexBufferLayout& layout)
{
	bind();
	buffer.bind();
	const auto& elements = layout.getElement();
	unsigned int offset = 0;
	for (unsigned int i=0; i<elements.size(); i++) 
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::unbind()
{
	glBindVertexArray(0);
}
