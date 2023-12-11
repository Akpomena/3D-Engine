#pragma once

namespace Engine
{
	class FrameBuffer
	{
	public:
		FrameBuffer(int width, int height);
		~FrameBuffer();

		void Bind();
		void UnBind();
		inline unsigned int GetTextureAttachment() { return m_TextureColourBuffer; }
	private:
		unsigned int m_FrameBuffer;
		unsigned int m_TextureColourBuffer;
		unsigned int m_RenderBufferObject;
	};
}


