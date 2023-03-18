#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"



DllExport VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_RendererID));
	}

DllExport VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_RendererID));
	}

DllExport	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();
		vb.Bind();
		const auto& elements = layout.GetElements();
		unsigned int offset = 0;

		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(i));
			GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset));
			offset += element.count * VertexbufferElement::GetSizeOfType(element.type);
		}

	}

DllExport void VertexArray::Bind() const
	{
		GLCall(glBindVertexArray(m_RendererID));
	}

DllExport void VertexArray::Unbind() const
	{
		GLCall(glBindVertexArray(0));
	}
