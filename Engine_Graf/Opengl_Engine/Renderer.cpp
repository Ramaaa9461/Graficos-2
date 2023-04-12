
#include "Renderer.h"

#include <iostream>


 Renderer* Renderer::S_Renderer = nullptr;

	void GLClearError()
	{
		while (glGetError() != GL_NO_ERROR);
	}

	bool GLLogCall(const char* funtion, const char* file, int line)
	{
		while (GLenum error = glGetError())
		{
			std::cout << "[OpenGL Error (" << error << "); " << funtion <<
				" " << file << ":" << line << std::endl;
			return false;
		}
		return true;
	}

	DllExport Renderer::Renderer()
	{
		initRenderer();
	}

	Renderer::~Renderer()
	{
		delete S_Renderer;
	}

	DllExport Renderer* Renderer::getRenderer()
	{
		if (S_Renderer == nullptr) {
			S_Renderer = new Renderer();
		}
		return S_Renderer;
	}

	DllExport	void Renderer::initRenderer()
	{
		Window* window = Window::getWindow();

		//proj = glm::ortho(0.0f, (float)window->WINDOW_WIDTH, 0.0f, (float)window->WINDOW_HEIGHT, -1.0f, 1.0f); //Proyeccion ortografica
		proj = glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f);
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, -10.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

	}


	DllExport void Renderer::Clear() const
	{
	//	GLCall(glClear(GL_COLOR_BUFFER_BIT));	
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}

	DllExport void Renderer::Draw(const VertexArray* va, const IndexBuffer* ib, const Shader* shader) const
	{
		shader->Bind();
		va->Bind();
		ib->Bind();

		GLCall(glDrawElements(GL_TRIANGLES, ib->GetCount(), GL_UNSIGNED_INT, nullptr));

	}

