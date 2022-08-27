#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, int count);
	~IndexBuffer();

	void bind() const;
	void unbind() const;
	inline unsigned int getCount() const { return m_Count; }
private:
	unsigned int m_RenderId;
	unsigned int m_Count;
};

