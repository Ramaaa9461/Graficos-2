#include "GL/glew.h"
#include "glfw3.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../Headers/Renderer.h"

#include "../Headers/VertexBuffer.h"
#include "../Headers/VertexBufferLayout.h"
#include "../Headers/IndexBuffer.h"
#include "../Headers/VertexArray.h"
#include "../Headers/Shader.h"
#include "../Headers/Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"


	int main(void)
	{

		GLFWwindow* window;

		/* Initialize the library */
		if (!glfwInit())
			return -1;

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		const int WINDOW_WIDTH = 960;
		const int WINDOW_HEIGHT = 540;


		window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			return -1;
		}

		glfwMakeContextCurrent(window);

		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK)
			std::cout << "Error!" << std::endl;

		std::cout << glGetString(GL_VERSION) << std::endl;
		{
			float positions[] = {
				-50.0f, -50.0f,	     0.0f, 0.0f,
				 50.0f, -50.0f,	     1.0f, 0.0f,
				 50.0f,  50.0f,	     1.0f, 1.0f,
				-50.0f,  50.0f,	     0.0f, 1.0f
			};

			unsigned int indices[] = {
				0,1,2,
				2,3,0
			};

			//GLCall(glEnable(GL_BLEND));
			//GLCall(glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA));   //TIENE QE VER CON BLENDING

			VertexArray va;
			VertexBuffer vb(positions, 4 * 4 * sizeof(float));

			VertexBufferLayout layout;
			layout.Push<float>(2);		 //Video: Buffer Layout Abstraction in OpenGL - min 27.30 Explica mas cosas qe se pueden hacer
			layout.Push<float>(2);
			va.AddBuffer(vb, layout);
			va.Bind();

			IndexBuffer ib(indices, 6);

			glm::mat4 proj = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, -1.0f, 1.0f); //Proyeccion ortografica
			glm::mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


			Shader shader("res/Shaders/Basic.shader");
			shader.Bind();
			shader.SetUniforms4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);


			Texture texture("res/textures/Logo.jpg");
			texture.Bind();
			shader.SetUniforms1i("u_Texture", 0);

			va.Unbind();
			vb.UnBind();
			ib.UnBind();
			shader.Unbind();

			Renderer renderer(window);

			ImGui::CreateContext();
			ImGui_ImplGlfwGL3_Init(window, true);
			ImGui::StyleColorsDark();

			glm::vec3 translation(200, 200, 0);
			glm::vec3 rotation(0, 0, 0);
			glm::vec3 scale(1, 1, 0);

			while (!glfwWindowShouldClose(window))
			{
				/* Render here */
				renderer.Clear();

				ImGui_ImplGlfwGL3_NewFrame();

				{ //Dibuja 1 objeto, si se duplica dibujas 2 :D
					glm::mat4 tras = glm::translate(glm::mat4(1.0f), translation);
					glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
					glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
					glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
					glm::mat4 sca = glm::scale(glm::mat4(1.0f), scale);

					glm::mat4 rot = rotX * rotY * rotZ;
					glm::mat4 model = tras * rot * sca;

					glm::mat4 mvp = proj * view * model;
					shader.Bind();
					shader.SetUniformsMat4f("u_MVP", mvp);
					renderer.Draw(&va, &ib, &shader);
				}
				{
					ImGui::SliderFloat3("Translation", &translation.x, 0.0f, WINDOW_WIDTH);
					ImGui::SliderFloat3("Rotation", &rotation.x, 0.0f, 360.0f);
					ImGui::SliderFloat3("Scale", &scale.x, 0.0f, 10.0f);

					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				}

				ImGui::Render();
				ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

				glfwSwapBuffers(window);
				glfwPollEvents();
			}
		}

		// Cleanup
		ImGui_ImplGlfwGL3_Shutdown();
		ImGui::DestroyContext();
		glfwTerminate();
		return 0;
	}

