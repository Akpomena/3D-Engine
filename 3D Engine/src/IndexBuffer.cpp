#include "IndexBuffer.h"
#include <glad/glad.h>

IndexBuffer::IndexBuffer(const unsigned int* data, int count):
    m_Count(count)
{
   // ASSERT(sizeof(unsigned int) != sizeof(GLint))

    glGenBuffers(1, &m_RenderId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RenderId);
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderId);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}