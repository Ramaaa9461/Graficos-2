#pragma once

#include "DDLExport.h"

class IndexBuffer
	{
	private:
		unsigned int m_RendererID;
		unsigned int m_Count;

	public:
		DllExport IndexBuffer(const unsigned* data, unsigned int count); //Video: Abstracing OPENGL into Classes - Min: 14.43
		DllExport ~IndexBuffer();

		DllExport void Bind() const;
		DllExport void UnBind() const;

		DllExport inline unsigned int GetCount() const { return m_Count; }
	};

