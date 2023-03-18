#pragma once

#include <vector>
#include "Renderer.h"


DllExport struct  VertexbufferElement
{
	unsigned int type;
	unsigned int count;
	char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexbufferElement> m_Elements;
	unsigned int m_Stride;

public:
	DllExport	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	DllExport void Push(int count)
	{
		static_assert(false);
	}

	template<>
	DllExport void Push<float>(int count) //Habria que cambiar unsigned int pero se rompe
	{
		VertexbufferElement vbe{ GL_FLOAT, count, GL_FALSE };
		m_Elements.push_back(vbe);
		m_Stride += count * VertexbufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	DllExport void Push<unsigned int>(int count)
	{
		VertexbufferElement vbe{ GL_UNSIGNED_INT, count, GL_FALSE };
		m_Elements.push_back(vbe);
		m_Stride += count * VertexbufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	DllExport void Push<char>(int count)
	{
		VertexbufferElement vbe{ GL_UNSIGNED_BYTE, count, GL_TRUE };
		m_Elements.push_back(vbe);
		m_Stride += count * VertexbufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	DllExport inline const std::vector<VertexbufferElement> GetElements() const { return m_Elements; }
	DllExport inline unsigned int GetStride() const { return m_Stride; }

};

