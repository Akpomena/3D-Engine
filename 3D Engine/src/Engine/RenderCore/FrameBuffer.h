#pragma once

namespace Engine
{

	struct FrameBufferProp
	{
		unsigned int Width;
		unsigned int Height;

		bool IsDepthBuffer;

		FrameBufferProp(unsigned int width = 800,
			unsigned int height = 600,
			bool isDepthBuffer = true) :
			Width(width), Height(height), IsDepthBuffer(isDepthBuffer)
		{
		}
	};

	class FrameBuffer
	{
	public:
		FrameBuffer(FrameBufferProp prop);
		~FrameBuffer();

		void Bind();
		void UnBind();
		inline unsigned int GetTextureAttachment() { return m_TextureColourBuffer; }
		void UpdateBufferSize(int width, int height);
	private:
		unsigned int m_FrameBuffer = 0;
		unsigned int m_TextureColourBuffer = 0;
		unsigned int m_RenderBufferObject = 0;

		FrameBufferProp m_Prop;
	};
}


