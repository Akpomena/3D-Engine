#pragma once

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, int count);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;
	inline unsigned int GetCount() const { return m_Count; }
private:
	unsigned int m_RenderId;
	unsigned int m_Count;
};

