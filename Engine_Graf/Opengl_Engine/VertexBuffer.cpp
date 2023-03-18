
#include "VertexBuffer.h"
#include "Renderer.h"


DllExport VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	{
		GLCall(glGenBuffers(1, &m_RendererID));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
	}

DllExport	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_RendererID));
	}

DllExport void VertexBuffer::updateVertexBufferData(const void* data, unsigned int size)
	{

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, data));
	}
	//https://stackoverflow.com/questions/27771902/opengl-changing-texture-coordinates-on-the-fly


DllExport	void VertexBuffer::Bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

DllExport void VertexBuffer::UnBind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

