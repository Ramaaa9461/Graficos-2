#pragma once

#include "DDLExport.h"

	class VertexBuffer
	{
	private:
		unsigned int m_RendererID;

	public:
		DllExport VertexBuffer(const void* data, unsigned int size);
		DllExport ~VertexBuffer();

		DllExport void updateVertexBufferData(const void* data, unsigned int size);

		DllExport void Bind() const;
		DllExport void UnBind() const;
	};

