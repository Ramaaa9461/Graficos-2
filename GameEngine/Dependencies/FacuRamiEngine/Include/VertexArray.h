#pragma once

#include "VertexBuffer.h"

	class VertexBufferLayout;



	class VertexArray
	{
	private:

		unsigned int m_RendererID;

	public:
		DllExport VertexArray();
		DllExport ~VertexArray();


		DllExport void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		DllExport void Bind() const;
		DllExport void Unbind() const;
	};

