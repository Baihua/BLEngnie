#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "BufferLayout.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "Shader.h"
#include "Texture.h"

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	const char* glsl_version = "#version 130";

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280, 720, "BigLine", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGl context" << std::endl;
	}

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	std::cout << glGetString(GL_VERSION) << std::endl;
	float h2Size = 256.0f / 2.f;
	float vertex[] = {
	    -h2Size, -h2Size, 0.0f, 0.0f,
		 h2Size, -h2Size, 1.0f, 0.0f,
		 h2Size,  h2Size, 1.0f, 1.0f,
		-h2Size,  h2Size, 0.0f, 1.0f,
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0,
	};
	
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
	GLCall(glfwSwapInterval(1));
	
	VertexBuffer vb(vertex, 4*4*sizeof(float));

	IndexBuffer ib(indices, 6);
	glm::mat4  proj = glm::ortho(0.f, 1280.f, 0.f, 720.f, -1.0f, 1.0f);
	glm::mat4 view = glm::translate(glm::mat4(1), glm::vec3(-50, 0, 0));
	
	VertexArray va;  
	BufferLayout layout;
	layout.push<float>(2);
	layout.push<float>(2);
	va.AddBuffer(vb, layout, ib);
	
	Shader shader("../../res/shader/base.shader");
	shader.Bind();
	//shader.SetUniformMat4f("u_MVP", proj*view*model);
	Texture texture("../../res/png/Res_123.png");
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);

	Renderer renderer;
	float r = 0;
	float increment = 0.05f;
	glm::vec3 translation(50.f, 0.f, 0.f);
	while (!glfwWindowShouldClose(window))
	{
		
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		renderer.Clear();
		texture.Bind();
		
		
		{
			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::SliderFloat3("move",&translation.x, 0, 960);
			
			
			glm::mat4 model = glm::translate(glm::mat4(1), translation);
			shader.SetUniformMat4f("u_MVP", proj * view * model);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		renderer.Draw(va, ib, shader);
		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	return 0;
}